#include <iostream>
#include <memory>

#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

template<typename T>
class MyUniquePtr
{
public:
   explicit MyUniquePtr(T* ptr = nullptr)
        :mPtr(ptr)
    {}

    ~MyUniquePtr()
    {
        if(mPtr)
            delete mPtr;
    }

    MyUniquePtr(MyUniquePtr &&p) noexcept;
    MyUniquePtr& operator=(MyUniquePtr &&p) noexcept;

    MyUniquePtr(const MyUniquePtr &p) = delete;
    MyUniquePtr& operator=(const MyUniquePtr &p) = delete;

    T* operator*() const noexcept {return mPtr;}
    T& operator->()const noexcept {return *mPtr;}
    explicit operator bool() const noexcept{return mPtr;}

    void reset(T* q = nullptr) noexcept
    {
        if(q != mPtr){
            if(mPtr)
                delete mPtr;
            mPtr = q;
        }
    }

    T* release() noexcept
    {
        T* res = mPtr;
        mPtr = nullptr;
        return res;
    }
    T* get() const noexcept {return mPtr;}
    void swap(MyUniquePtr &p) noexcept
    {
        using std::swap;
        swap(mPtr, p.mPtr);
    }
private:
    T* mPtr;
};

template<typename T>
MyUniquePtr<T>& MyUniquePtr<T>::operator=(MyUniquePtr &&p) noexcept
{
    swap(*this, p);
    return *this;
}

template<typename T>
MyUniquePtr<T> :: MyUniquePtr(MyUniquePtr &&p) noexcept : mPtr(p.mPtr)
{
    p.mPtr == nullptr;
}

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  std::unique_ptr<int> uptr(new int(10));  //绑定动态对象
  // std::unique_ptr<int> uptr2 = uptr;  //不能賦值
  // std::unique_ptr<int> uptr2(uptr);  //不能拷貝
  std::unique_ptr<int> uptr2 = std::move(uptr);  //轉換所有權
  uptr2.release();                               //释放所有权

  MyUniquePtr<int> m_uptr(new int(10));
  MyUniquePtr<int> m_uptr2 = std::move(m_uptr);
  m_uptr2.release();

  return 0;
}
