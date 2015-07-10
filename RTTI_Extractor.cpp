#include <xlib.h>

DWORD WINAPI StartCLR(PVOID lParam);

//! 使用全局变量初始化CLR窗口避免x64 DLL混合编程的初始化问题
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

  窗口上部控件为：【关闭X】、【最小化N】【窗口移动】
  【地址A】接受需要解析的内存地址
  【长度L】接受需要解析的内存长度，限制为0～FFFF，缺省为200
  【详细M】选中时，将深入一层解析
  【标准库S】选中时，将RTTI解析失败的地址尝试解析为string、wstring、vector、map
  【解析E】按钮开始解析指定内存
  其下为【信息输出控件】，双击清除
*/