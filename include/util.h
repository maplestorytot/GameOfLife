//
// Created by ryan on 09/05/22.
//

#ifndef GAMEOFLIFE_UTIL_H
#define GAMEOFLIFE_UTIL_H
#define DECLARE_CLASS_AS_INTERFACE(ClassName)                                \
   public :                                                                  \
      virtual ~ClassName() {}                                                \
   protected :                                                               \
      ClassName() {}                                                         \
      ClassName(const ClassName & ) {}                                       \
      ClassName & operator = (const ClassName & ) { return *this ; }         \
      ClassName(ClassName && ) noexcept {}                                   \
      ClassName & operator = (ClassName && ) noexcept { return *this ; }     \
   private :
#endif //GAMEOFLIFE_UTIL_H
