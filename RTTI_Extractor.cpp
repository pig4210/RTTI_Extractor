#include <xlib.h>

DWORD WINAPI StartCLR(PVOID lParam);

//! ʹ��ȫ�ֱ�����ʼ��CLR���ڱ���x64 DLL��ϱ�̵ĳ�ʼ������
static HANDLE hThd = CreateThread(nullptr, 0, StartCLR, nullptr, 0, nullptr);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
  {
  UNREFERENCED_PARAMETER(hModule);
  UNREFERENCED_PARAMETER(lpReserved);
  switch(ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      TerminateThread(hThd, 0);
      break;
    }
  return TRUE;
  }

/*
struct TypeDescriptor
  {
  DWORD ptrToVTable;
  DWORD spare;
  char name[8];
  };

struct PMD
  {
  int mdisp;  //member displacement
  int pdisp;  //vbtable displacement
  int vdisp;  //displacement inside vbtable
  };
struct RTTIBaseClassDescriptor
  {
  struct TypeDescriptor* pTypeDescriptor; //type descriptor of the class
  DWORD numContainedBases; //number of nested classes following in the Base Class Array
  struct PMD where;        //pointer-to-member displacement info
  DWORD attributes;        //flags, usually 0
  };

struct RTTIClassHierarchyDescriptor
  {
  DWORD signature;      //always zero?
  DWORD attributes;     //bit 0 set = multiple inheritance, bit 1 set = virtual inheritance
  DWORD numBaseClasses; //number of classes in pBaseClassArray
  struct RTTIBaseClassArray* pBaseClassArray;
  };

struct RTTICompleteObjectLocator
  {
  DWORD signature; //always zero ?
  DWORD offset;    //offset of this vtable in the complete class
  DWORD cdOffset;  //constructor displacement offset
  struct TypeDescriptor* pTypeDescriptor; //TypeDescriptor of the complete class
  struct RTTIClassHierarchyDescriptor* pClassDescriptor; //describes inheritance hierarchy
  };

  �����ϲ��ؼ�Ϊ�����ر�X��������С��N���������ƶ���
  ����ַA��������Ҫ�������ڴ��ַ
  ������L��������Ҫ�������ڴ泤�ȣ�����Ϊ0��FFFF��ȱʡΪ200
  ����ϸM��ѡ��ʱ��������һ�����
  ����׼��S��ѡ��ʱ����RTTI����ʧ�ܵĵ�ַ���Խ���Ϊstring��wstring��vector��map
  ������E����ť��ʼ����ָ���ڴ�
  ����Ϊ����Ϣ����ؼ�����˫�����
*/