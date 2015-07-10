#include "dlg.h"

#include <string>

#include <gcroot.h>

#include <xlib.h>

static const wchar_t* const gk_app_name = L"RTTI��Ϣ��ȡ";
static const wchar_t* const gk_app_ver = L"ver 1.0";
static const wchar_t* const gk_author = L"by triones";
static const wchar_t* const gk_copyright = L"All rights reserved (c)";

using namespace std;
using namespace RTTI_Extractor;

//! �߳�����ʹ���DLL�ɹ�����CLR����
static gcroot <dlg^> mydlg = nullptr;
DWORD WINAPI StartCLR(PVOID lParam)
  {
  UNREFERENCED_PARAMETER(lParam);
  mydlg = gcnew dlg;
  mydlg->ShowDialog();
  return 0;
  }

//! ���������Ϣ��Ҳ����������ص�
void showinfo(const char* const buf)
  {
  mydlg->TB_mem->AppendText(gcnew System::String(buf));
  }

//! ���ڼ��س�ʼ��
System::Void dlg::dlg_Load(System::Object^  sender, System::EventArgs^  e)
  {
  UNREFERENCED_PARAMETER(sender);
  UNREFERENCED_PARAMETER(e);

  wchar_t procname[MAX_PATH];
  GetModuleFileNameW(nullptr, procname, _countof(procname));

  //������
  wstring title;
  title += procname;
  title += L"--";
  title += gk_app_name;
  title += L"  ";
  title += gk_app_ver;
  title += L"  ";
  title += gk_author;
  title += L"  ";
  title += gk_copyright;
  this->Text = gcnew System::String(title.c_str());

  TB_Start->MaxLength = sizeof(void*)* 2 + sizeof(void*) - 1;
#ifdef _WIN64
  TB_Start->MaxLength += 2;
#endif
  }

//! ���ڹر�
System::Void dlg::Btn_Close_Click(System::Object^  sender, System::EventArgs^  e)
  {
  UNREFERENCED_PARAMETER(sender);
  UNREFERENCED_PARAMETER(e);
  Close();
  }

//! ������С��
System::Void dlg::Btn_Min_Click(System::Object^  sender, System::EventArgs^  e)
  {
  UNREFERENCED_PARAMETER(sender);
  UNREFERENCED_PARAMETER(e);
  this->WindowState = FormWindowState::Minimized;
  }

//! �����ƶ�
System::Void dlg::LB_Pos_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
  {
  UNREFERENCED_PARAMETER(sender);
  UNREFERENCED_PARAMETER(e);
  ReleaseCapture();
  SendMessage((HWND)this->Handle.ToPointer(), WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
  }

//! ����ʮ�����Ƶ�ַ����
System::Void dlg::TB_Start_TextChanged(System::Object^  sender, System::EventArgs^  e)
  {
  UNREFERENCED_PARAMETER(sender);
  UNREFERENCED_PARAMETER(e);
  TextBox^ tb = (TextBox^)sender;

  if(System::String::IsNullOrEmpty(tb->Text)) return;

  //��ȡ�ı�����
  const wchar_t* tmplp = (wchar_t*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(tb->Text);

  const wstring src(tmplp);

  //ע���ͷ���Դ
  System::Runtime::InteropServices::Marshal::FreeHGlobal((System::IntPtr)(void*)tmplp);

  wstring hexstr;

  //��ʼ�����ı���ʶ��ʮ������
  for(auto ch : src)
    {
    if(hexstr.size() >= (sizeof(void*)* 2))   break;  //�����㹻�������������

    wchar_t dch;
    switch(ch)
      {
      case L'0':      case L'1':      case L'2':      case L'3':
      case L'4':      case L'5':      case L'6':      case L'7':
      case L'8':      case L'9':
      case L'A':      case L'B':      case L'C':      case L'D':
      case L'E':      case L'F':
        dch = ch;
        break;
      case L'a':      case L'b':      case L'c':      case L'd':
      case L'e':      case L'f':
        dch = ch - L'a' + L'A';
        break;
      default: continue;
      }

    hexstr.push_back(dch);
    }

  //����ʮ�����Ƶ�ַ��ʾ��ʽ
  wstring dest;
  for(wstring::const_reverse_iterator it = hexstr.rbegin(); it != hexstr.rend(); ++it)
    {
    dest.insert(dest.begin(), *it);
    switch(dest.size())
      {
      case 3:   case 6:   case 9:
      case 17:  case 20:  case 23:
        dest.insert(1, 1, L' ');
        break;
      case 12:
        dest.insert(1, 1, L' ');
        dest.insert(1, 1, L'`');
        dest.insert(1, 1, L' ');
        break;
      default:
        break;
      }
    }

  System::String^ cur_str = gcnew System::String(dest.c_str());

  //�Ƚ��ı��Ƿ���Ҫ�޸�
  if(cur_str->CompareTo(tb->Text) != 0)
    {
    tb->Text = cur_str;
    //�ı��޸ĺ���Ҫ�ı���λ�ã�����򵥵Ĵ���ָ���ı����һ���ַ�
    tb->SelectionStart = tb->MaxLength;
    }
  }

extern void*   g_start;
extern size_t  g_len;
extern bool    g_more_info;
extern bool    g_stl;
DWORD WINAPI Thd(PVOID lParam);

static HANDLE  g_thd = nullptr;

System::Void dlg::Btn_Match_Click(System::Object^  sender, System::EventArgs^  e)
  {
  UNREFERENCED_PARAMETER(sender);
  UNREFERENCED_PARAMETER(e);
  //�ж��ϴι����߳��Ƿ��������δ����������ʾ����
  if(g_thd != nullptr)
    {
    if(WAIT_OBJECT_0 != WaitForSingleObject(g_thd, 0))
      {
      if(MessageBox::Show(
        L"��һ�εĽ������̻�û�������Ƿ�ȴ���\n\n�粻�ȴ���ѡ��'��'����ǿ�ƽ���֮ǰ�Ĺ���",
        L"����", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) != ::DialogResult::No)
        {
        return;
        }
      TerminateThread(g_thd, 0);
      xmsg msg;
      msg << "�ϴεĹ���:" << g_thd << " �ֱ�ǿ�ƹر�\r\n";
      showinfo(msg.c_str());
      }
    }
  g_thd = nullptr;

  //�ж���ַ�ͳ�����Ч��
  if(System::String::IsNullOrEmpty(TB_Start->Text))
    {
    tp->Show("������ڴ��ַ", TB_Start, 10, 10, 3000);
    TB_Start->Focus();
    return;
    }
  if(System::String::IsNullOrEmpty(TB_Len->Text))
    {
    TB_Len->Text = "200";
    }

  g_more_info = CB_More->Checked;
  g_stl = CB_STL->Checked;
  //��ȡ��ַ
  const char* s[2];
  s[0] = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(TB_Start->Text);
  s[1] = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(TB_Len->Text);

  void* p[_countof(s)];
  for(size_t i = 0; i < _countof(s); ++i)
    {
    size_t pp = 0;
    for(const char* str = s[i]; *str != '\0'; ++str)
      {
      switch(*str)
        {
        case '0':      case '1':      case '2':      case '3':
        case '4':      case '5':      case '6':      case '7':
        case '8':      case '9':
          pp <<= 4;
          pp += ((*str) - '0');
          break;
        case 'A':      case 'B':      case 'C':      case 'D':
        case 'E':      case 'F':
          pp <<= 4;
          pp += ((*str) - 'A') + 0xA;
          break;
        case 'a':      case 'b':      case 'c':      case 'd':
        case 'e':      case 'f':
          pp <<= 4;
          pp += ((*str) - 'a') + 0xA;
          break;
        default: break;
        }
      }
    p[i] = (void*)pp;
    }

  System::Runtime::InteropServices::Marshal::FreeHGlobal((System::IntPtr)(void*)s[0]);
  System::Runtime::InteropServices::Marshal::FreeHGlobal((System::IntPtr)(void*)s[1]);

  g_start = p[0];
  g_len = (size_t)p[1];

  g_thd = CreateThread(nullptr, 0, Thd, nullptr, 0, nullptr);
  }

//! �ı����
System::Void dlg::TB_mem_DoubleClick(System::Object^  sender, System::EventArgs^  e)
  {
  UNREFERENCED_PARAMETER(sender);
  UNREFERENCED_PARAMETER(e);
  TB_mem->Clear();
  }