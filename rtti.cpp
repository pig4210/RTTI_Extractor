#include <xlib.h>

#include <tchar.h>
#include <string>

using namespace std;

void showinfo(const char* const buf);

class rtti_log : public xmsg
  {
  public:
    virtual ~rtti_log()
      {
      if(empty()) return;
      append("\r\n");
      showinfo(c_str());
      clear();
      }
  };

#define rlog rtti_log()

#ifdef _WIN64
static void* PickRttiOffset(const __int32* mem)
  {
  MEMORY_BASIC_INFORMATION mbi;
  if(VirtualQuery(mem, &mbi, sizeof(mbi)) != sizeof(mbi))
    {
    return nullptr;
    }
  return (void*)((size_t)mbi.AllocationBase + (*mem));
  }
#endif

extern "C"
void* __cdecl __unDNameHelper(char * outputString,
                              const char * name,
                              int maxStringLength,
                              unsigned short disableFlags);

#pragma pack(push,1)
struct PMD
  {
  __int32     mdisp;
  __int32     pdisp;
  __int32     vdisp;
  };

struct RTTIBaseClassDescriptor
  {
#ifndef _WIN64
  struct TypeDescriptor*          pTypeDescriptor;
#else
  __int32                         dispTypeDescriptor;
#endif
  unsigned __int32                numContainedBases;
  PMD                             wheres;
  unsigned __int32                attributes;

  const type_info* GetTypeDescriptor() const;
  };

struct RTTIClassHierarchyDescriptor
  {
  unsigned __int32                signature;
  unsigned __int32                attributes;
  unsigned __int32                numBaseClasses;
#ifndef _WIN64
  struct RTTIBaseClassArray*      pBaseClassArray;
#else
  __int32                         dispBaseClassArray;
#endif
  const RTTIBaseClassDescriptor* GetBaseClass(const size_t num) const;
  };

struct RTTICompleteObjectLocator
  {
  unsigned __int32                signature;
  unsigned __int32                offset;
  unsigned __int32                cdOffset;
#ifndef _WIN64
  struct TypeDescriptor*          pTypeDescriptor;
  RTTIClassHierarchyDescriptor*   pClassDescriptor;
#else
  __int32                         dispTypeDescriptor;
  __int32                         dispClassDescriptor;
#endif
  const type_info* GetTypeDescriptor() const;
  const RTTIClassHierarchyDescriptor* GetClassDescriptor() const;
  };
#pragma pack(pop)


const type_info* RTTIBaseClassDescriptor::GetTypeDescriptor() const
  {
#ifndef _WIN64
  return (const type_info*)pTypeDescriptor;
#else
  return (const type_info*)PickRttiOffset(&dispTypeDescriptor);
#endif
  }

const RTTIBaseClassDescriptor* RTTIClassHierarchyDescriptor::GetBaseClass(const size_t num) const
  {
#ifndef _WIN64
  const RTTIBaseClassDescriptor** p = (const RTTIBaseClassDescriptor**)pBaseClassArray;
  return (const RTTIBaseClassDescriptor*)p[num];
#else
  const __int32* p = (const __int32*)PickRttiOffset(&dispBaseClassArray);
  return (const RTTIBaseClassDescriptor*)PickRttiOffset(&p[num]);
#endif
  }

const type_info* RTTICompleteObjectLocator::GetTypeDescriptor() const
  {
#ifndef _WIN64
  return (const type_info*)pTypeDescriptor;
#else
  return (const type_info*)PickRttiOffset(&dispTypeDescriptor);
#endif
  }

const RTTIClassHierarchyDescriptor* RTTICompleteObjectLocator::GetClassDescriptor() const
  {
#ifndef _WIN64
  return pClassDescriptor;
#else
  return (const RTTIClassHierarchyDescriptor*)PickRttiOffset(&dispClassDescriptor);
#endif
  }


void*   g_start = nullptr;
size_t  g_len = 0;
bool    g_more_info = false;
bool    g_stl = false;

#ifndef _WIN64
static const unsigned __int32 gk_rtti_signature = 0x0;
#else
static const unsigned __int32 gk_rtti_signature = 0x1;
#endif

static bool RttiAnaly(void* mem)
  {
  void** vtable = nullptr;

  const RTTICompleteObjectLocator* rtticol = nullptr;

  const char* flag = "↓";

  try
    {
    vtable = *((void***)mem);

    rtticol = (const RTTICompleteObjectLocator*)*(vtable - 1);

    if(rtticol->signature != gk_rtti_signature)
      {
      vtable = nullptr;
      }
    }
  catch(...)
    {
    vtable = nullptr;
    }

  try
    {
    if(vtable == nullptr)
      {
      vtable = **((void****)mem);
      rtticol = (const RTTICompleteObjectLocator*)*(vtable - 1);

      if(rtticol->signature != gk_rtti_signature) return false;
      flag = "→";
      }

    const type_info* ti = rtticol->GetTypeDescriptor();

    const char* name = ti->name();

    const char* type = "◆";

    if(_strnicmp(name, "class ", 6) == 0)
      {
      type = "●";
      name += 6;
      }
    else
      {
      if(_strnicmp(name, "struct ", 7) == 0)
        {
        type = "○";
        name += 7;
        }
      }

    xmsg msg;

    msg << "\r\n" << mem << ' ' << flag << ' ' << type << name;

    if(!g_more_info)
      {
      rlog << msg;
      return true;
      }

    const RTTIClassHierarchyDescriptor* rchd = rtticol->GetClassDescriptor();

    if(rchd == nullptr) return true;

    if(rchd->signature != 0)  return false;   //标志判定

    for(size_t i = 1; i < rchd->numBaseClasses; ++i)
      {
      msg << ((i == 1) ? " : " : " , ");

      const RTTIBaseClassDescriptor* rbc = rchd->GetBaseClass(i);

      name = rbc->GetTypeDescriptor()->name();

      type = "◆";

      if(_strnicmp(name, "class ", 6) == 0)
        {
        type = "●";
        name += 6;
        }
      else
        {
        if(_strnicmp(name, "struct ", 7) == 0)
          {
          type = "○";
          name += 7;
          }
        }

      msg << type << name;
      }
    
    rlog << msg;
    return true;
    }
  catch(...)
    {
    ;
    }
  return false;
  }

static bool AnalyString(const string* s)
  {
  try
    {
    if((intptr_t)s->size() < 0) return false;
    if((intptr_t)s->capacity() <= (intptr_t)s->size())  return false;
    if(s->size() > 0x00800000)  return false;
    if(s->capacity() > 0x00800000)  return false;
    if(strlen(s->c_str()) != s->size()) return false;
    const size_t mask = s->_ALLOC_MASK + 1;
    if((mask * ((s->size() / mask) + 1) - 1) != s->capacity())  return false;
    return true;
    }
  catch(...)
    {

    }
  return false;
  }

static bool AnalyWstring(const wstring* ws)
  {
  try
    {
    if((intptr_t)ws->size() < 0) return false;
    if((intptr_t)ws->capacity() <= (intptr_t)ws->size())  return false;
    if(ws->size() > 0x00800000)  return false;
    if(ws->capacity() > 0x00800000)  return false;
    if(wcslen(ws->c_str()) != ws->size()) return false;
    const size_t mask = ws->_ALLOC_MASK + 1;
    if((mask * ((ws->size() / mask) + 1) - 1) != ws->capacity())  return false;
    return true;
    }
  catch(...)
    {

    }
  return false;
  }

struct f_vector
  {
  public:
    const unsigned char* _Myfirst;
    const unsigned char* _Mylast;
    const unsigned char* _Myend;
  };

static bool AnalyVector(const f_vector* vec)
  {
  try
    {
    if(vec->_Myfirst == nullptr)  return false;
    if(vec->_Mylast == nullptr) return false;
    if(vec->_Myend == nullptr)  return false;
    if((size_t)vec->_Myfirst > (size_t)vec->_Mylast)  return false;
    if((size_t)vec->_Mylast > (size_t)vec->_Myend)  return false;
    if((intptr_t)(vec->_Mylast - vec->_Myfirst) >= 0x00800000) return false;
    char ch = *(vec->_Myfirst);
    ch += *(vec->_Mylast);
    ch += *(vec->_Myend);
    return true;
    }
  catch(...)
    {

    }
  return false;
  }

struct f_map_node
  {
  public:
    const f_map_node* _Left;
    const f_map_node* _Parent;
    const f_map_node* _Right;
  };

struct f_map
  {
  public:
    const f_map_node* _Myhead;
    size_t            _Mysize;
  };

static bool AnalyMap(const f_map* m)
  {
  try
    {
    if((intptr_t)m->_Mysize < 0) return false;
    if(m->_Myhead == nullptr) return false;
    if(m->_Myhead->_Left == nullptr)  return false;
    if(m->_Myhead->_Right== nullptr) return false;
    if(m->_Myhead->_Parent == nullptr) return false;
    if(m->_Mysize >= 0x00800000) return false;
    if(m->_Myhead->_Left->_Left == nullptr)  return false;
    if(m->_Myhead->_Left->_Right == nullptr)  return false;
    if(m->_Myhead->_Left->_Parent == nullptr)  return false;
    if(m->_Myhead->_Right->_Left == nullptr) return false;
    if(m->_Myhead->_Right->_Right == nullptr) return false;
    if(m->_Myhead->_Right->_Parent == nullptr) return false;
    if(m->_Myhead->_Parent->_Left == nullptr) return false;
    if(m->_Myhead->_Parent->_Right == nullptr) return false;
    if(m->_Myhead->_Parent->_Parent == nullptr) return false;
    return true;
    }
  catch(...)
    {

    }
  return false;
  }

//! 注意判定的先后顺序有讲究
static size_t ExpandAnaly(void* mem)
  {
  //先判定地址
  if(((size_t)mem % sizeof(__int32)) != 0)  return 0;
  //判定wstring
  const wstring* ws = (const wstring*)mem;
  if(AnalyWstring(ws))
    {
    rlog << "\r\n" << mem << " ↓ 〓wstring ("<< (intptr_t)ws->size() << ") : " << ws->c_str();
    return sizeof(wstring);
    }
  //判定string
  const string* s = (const string*)mem;
  if(AnalyString(s))
    {
    rlog << "\r\n" << mem << " ↓ ≈string (" << (intptr_t)s->size() << ") : " << s->c_str();
    return sizeof(string);
    }
  //判定map
  const f_map* m = (const f_map*)mem;
  if(AnalyMap(m))
    {
    rlog << "\r\n" << mem << " ↓ ★map " << (void*)m->_Mysize;
    return sizeof(f_map);
    }
  //判定vector
  const f_vector* vec = (const f_vector*)mem;
  if(AnalyVector(vec))
    {
    rlog << "\r\n" << mem << " ↓ ☆vector " << (void*)(vec->_Mylast - vec->_Myfirst);
    return sizeof(f_vector);
    }

  if(!g_more_info)  return 0;

  ws = (const wstring*)mkP(mem);
  if(AnalyWstring(ws))
    {
    rlog << "\r\n" << mem << " → 〓wstring (" << (intptr_t)ws->size() << ") : " << ws->c_str();
    return sizeof(void*);
    }
  s = (const string*)mkP(mem);
  if(AnalyString(s))
    {
    rlog << "\r\n" << mem << " → ≈string (" << (intptr_t)s->size() << ") : " << s->c_str();
    return sizeof(void*);
    }
  m = (const f_map*)mkP(mem);
  if(AnalyMap(m))
    {
    rlog << "\r\n" << mem << " → ★map " << (void*)m->_Mysize;
    return sizeof(void*);
    }
  vec = (const f_vector*)mkP(mem);
  if(AnalyVector(vec))
    {
    rlog << "\r\n" << mem << " → ☆vector " << (void*)(vec->_Mylast - vec->_Myfirst);
    return sizeof(void*);
    }
  return 0;
  }

DWORD WINAPI Thd(PVOID lParam)
  {
  UNREFERENCED_PARAMETER(lParam);
  try
    {
    const DWORD start_time = GetTickCount();
    rlog << "\r\n\r\n------------------------解析工作开始------------------------"
      << "  " << g_start << ":" << (intptr_t)g_len;

    for(size_t s = 0; s < g_len;)
      {
      if(RttiAnaly(g_start))
        {
        g_start = (void*)((size_t)g_start + sizeof(void*));
        s += sizeof(void*);
        }
      else
        {
        const size_t len = (g_stl ? ExpandAnaly(g_start) : 0);
        if(len == 0)
          {
          g_start = (void*)((size_t)g_start + 1);
          ++s;
          }
        else
          {
          g_start = (void*)((size_t)g_start + len);
          s += len;
          }
        }
      }

    const DWORD end_time = GetTickCount();
    rlog << "\r\n------------------------解析工作结束------------------------\t"
      << (int)(end_time - start_time) << "ms";
    return 0;
    }
  catch(...)
    {
    ;
    }
  rlog << "----------------解析工作出现未知异常，失败！----------------";
  return 0;
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

static void RttiAnaly(void* mem)
  {
  void** vtable = nullptr;
  try
    {
    vtable = *((void***)mem);

    const RTTICompleteObjectLocator* rtticol = (const RTTICompleteObjectLocator*)*(vtable - 1);

    const type_info* ti = rtticol->GetTypeDescriptor();

    rlog << "●"<< mem << "  " << ti->name() << "  --  "
      << "sign:" << rtticol->signature
      << "  offset:" << rtticol->offset
      << "  cdOffset:" << rtticol->cdOffset;

    const RTTIClassHierarchyDescriptor* rchd = rtticol->GetClassDescriptor();

    rlog << "  sig:" << rchd->signature
      << "  attr:" << rchd->attributes
      << "  num:" << rchd->numBaseClasses;

    const RTTIBaseClassDescriptor** rbcd = rchd->GetBaseClassArray();


    for(size_t i = 0; i < rchd->numBaseClasses; ++i)
      {
      const RTTIBaseClassDescriptor& rbc = *(rbcd[i]);
      rlog << "        " << (intptr_t)i << ":" << rbc.GetTypeDescriptor()->name()
        << "  num:" << rbc.numContainedBases
        << "  mdisp:" << rbc.wheres.mdisp
        << "  pdisp:" << rbc.wheres.pdisp
        << "  vdisp:" << rbc.wheres.vdisp
        << "  attr:" << rbc.attributes;
      }

    }
  catch(...)
    {
    ;
    }
  }
*/