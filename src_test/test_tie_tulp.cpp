#include <string>
#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"

#include "lib.h"

#define PRIVATE_TEST 1
#include "custom_tie_tuple.h"

TEST(version, test1)
{
      ASSERT_TRUE(version() > 0);
}


class CustomTupleTest : public testing::Test
{
  public:
      void SetUp() {}
      void TearDown() {}
};


TEST_F(CustomTupleTest, DefaultCtor)
{
      custom_tuple ctup;
      ASSERT_EQ(ctup.list_binding_args.size(), 0);
}

TEST_F(CustomTupleTest, CustomCtor1)
{
      std::string str1 = "str1";
      int iVar = 10;
      custom_tuple ctup(str1, iVar);

      ASSERT_EQ(ctup.list_binding_args.size(), 2);
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup.list_binding_args[0])).get() == "str1");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup.list_binding_args[1])).get() == 10);

      str1 = "str2";
      iVar = 20;

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup.list_binding_args[0])).get() == "str2");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup.list_binding_args[1])).get() == 20);
}

TEST_F(CustomTupleTest, CopyCtor)
{
      std::string str1 = "str1";
      int iVar = 10;
      custom_tuple ctup1(str1, iVar);

      custom_tuple ctup2(ctup1);

      ASSERT_EQ(ctup1.list_binding_args.size(), 2);
      ASSERT_EQ(ctup2.list_binding_args.size(), 2);

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup1.list_binding_args[0])).get() == "str1");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup1.list_binding_args[1])).get() == 10);
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup2.list_binding_args[0])).get() == "str1");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup2.list_binding_args[1])).get() == 10);
}

TEST_F(CustomTupleTest, MoveCtor)
{
      std::string str1 = "str1";
      int iVar = 10;
      custom_tuple ctup1(str1, iVar);

      custom_tuple ctup2(std::move(ctup1));

      ASSERT_EQ(ctup1.list_binding_args.size(), 0);
      ASSERT_EQ(ctup2.list_binding_args.size(), 2);

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup2.list_binding_args[0])).get() == "str1");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup2.list_binding_args[1])).get() == 10);
}

TEST_F(CustomTupleTest, swap)
{
      std::string str1 = "str1";
      int iVar = 10;
      custom_tuple ctup1(str1, iVar);
      custom_tuple ctup2;

      ctup2.swap(ctup1);

      ASSERT_EQ(ctup1.list_binding_args.size(), 0);
      ASSERT_EQ(ctup2.list_binding_args.size(), 2);

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup2.list_binding_args[0])).get() == "str1");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup2.list_binding_args[1])).get() == 10);
}

TEST_F(CustomTupleTest, CopyAssignment)
{
      std::string str1 = "str1";
      int iVar = 10;
      custom_tuple ctup1(str1, iVar);
      custom_tuple ctup2;

      ctup2 = ctup1;

      ASSERT_EQ(ctup1.list_binding_args.size(), 2);
      ASSERT_EQ(ctup2.list_binding_args.size(), 2);

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup1.list_binding_args[0])).get() == "str1");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup1.list_binding_args[1])).get() == 10);
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup2.list_binding_args[0])).get() == "str1");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup2.list_binding_args[1])).get() == 10);

      str1 = "str2";
      iVar = 20;

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup1.list_binding_args[0])).get() == "str2");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup1.list_binding_args[1])).get() == 20);
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup2.list_binding_args[0])).get() == "str2");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup2.list_binding_args[1])).get() == 20);
}

TEST_F(CustomTupleTest, MoveAssignment)
{
      std::string str1 = "str1";
      int iVar = 10;
      custom_tuple ctup1(str1, iVar);
      custom_tuple ctup2;

      ctup2 = std::move(ctup1);

      ASSERT_EQ(ctup1.list_binding_args.size(), 0);
      ASSERT_EQ(ctup2.list_binding_args.size(), 2);

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup2.list_binding_args[0])).get() == "str1");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup2.list_binding_args[1])).get() == 10);

      str1 = "str2";
      iVar = 20;

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup2.list_binding_args[0])).get() == "str2");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup2.list_binding_args[1])).get() == 20);
}

TEST_F(CustomTupleTest, TupleAssignment)
{
      std::string str1 = "str1";
      int iVar1 = 10;
      custom_tuple ctup(str1, iVar1);

      std::string str2 = "str2";
      int iVar2 = 20;
      auto tpl = std::make_tuple(str2, iVar2);

      ctup = tpl;

      ASSERT_EQ(ctup.list_binding_args.size(), 2);

      ASSERT_TRUE((std::any_cast<std::reference_wrapper<std::string>>(ctup.list_binding_args[0])).get() == "str2");
      ASSERT_TRUE((std::any_cast<std::reference_wrapper<int>>(ctup.list_binding_args[1])).get() == 20);
      ASSERT_TRUE(str1 == "str2");
      ASSERT_TRUE(iVar1 == 20);
}

TEST(CustomTupleUtility, TupleSize)
{
      std::string str1 = "str1";
      int iVar1 = 10;
      custom_tuple ctup(str1, iVar1);

      ASSERT_TRUE(std::tuple_size<decltype(ctup)>::value == 2);
}

TEST(CustomTupleUtility, get)
{
      std::string str1 = "str1";
      int iVar1 = 10;
      auto& [a, b] = custom_tuple(str1, iVar1);

      ASSERT_TRUE(a == "str1");
      ASSERT_TRUE(b == 10);

      a = "qqq";
      b = 20;

      ASSERT_TRUE(str1 == "qqq");
      ASSERT_TRUE(iVar1 == 20);
}
