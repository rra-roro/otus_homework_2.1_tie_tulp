#pragma once

#include <any>
#include <vector>
#include <tuple>
#include <type_traits>

template <typename... Types>
class custom_tuple;

namespace std
{
      template <class... _Types>
      struct tuple_size<custom_tuple<_Types...>>
          : integral_constant<size_t, sizeof...(_Types)>
      { // size of tuple
      };

      template <size_t _Index>
      struct tuple_element<_Index, custom_tuple<>>
      { // enforce bounds checking
            static_assert(_Always_false<integral_constant<size_t, _Index>>,
                "tuple index out of bounds");
      };

      template <class _This,
          class... _Rest>
      struct tuple_element<0, custom_tuple<_This, _Rest...>>
      { // select first element
            using type = _This;
            using _Ttype = custom_tuple<_This, _Rest...>;
      };

      template <size_t _Index,
          class _This,
          class... _Rest>
      struct tuple_element<_Index, custom_tuple<_This, _Rest...>>
          : public tuple_element<_Index - 1, custom_tuple<_Rest...>>
      { // recursive tuple_element definition
      };

}




template <typename... Types>
class custom_tuple
{
  public:
      template <typename... Types>
      custom_tuple(const custom_tuple<Types...>& other) : list_binding_args(other.list_binding_args)
      {
      }

      template <typename... Types>
      custom_tuple(custom_tuple<Types...>&& other) : list_binding_args(std::move(other.list_binding_args))
      {
      }

      custom_tuple(Types&... args)
      {
            if constexpr (sizeof...(args) != 0)
            {
                  list_binding_args.reserve(sizeof...(args));

                  bool arr[sizeof...(args)] = { (list_binding_args.push_back(std::any(std::ref(args))), false)... };
            }
      };

      template <typename... Types>
      custom_tuple& operator=(const custom_tuple<Types...>& other)
      {
            list_binding_args = other.list_binding_args;
            return *this;
      }

      template <typename... Types>
      custom_tuple& operator=(custom_tuple<Types...>&& other)
      {
            list_binding_args.swap(other.list_binding_args);
            return *this;
      }

      template <typename... TypesTuple>
      auto operator=(const std::tuple<TypesTuple...>& arg)
      {
            static_assert(sizeof...(TypesTuple) == sizeof...(Types), "custom_tuple size and tuple size are different");

            assignment<std::tuple_size_v<std::tuple<TypesTuple...>> - 1, TypesTuple...>(arg);
            return this;
      }

      template <typename... Types>
      void swap(custom_tuple<Types...>& other)
      {
            list_binding_args.swap(other.list_binding_args);
      }

      template <typename... Types>
      friend class custom_tuple;

      template <size_t Index>
      auto& get() noexcept
      { 
            using type = typename std::tuple_element<Index, custom_tuple<Types...>>::type;
            std::reference_wrapper<type> ref = std::any_cast<std::reference_wrapper<type>>(list_binding_args[Index]);
            return ref.get();
      }
      
  private:
      std::vector<std::any> list_binding_args;

      template <size_t Index, typename... TypesTuple>
      void assignment(const std::tuple<TypesTuple...>& arg)
      {
            if constexpr (Index > 0)
                  assignment<Index - 1, TypesTuple...>(arg);

            using t_element = typename std::tuple_element<Index, std::tuple<TypesTuple...>>::type;
            using ct_element = typename std::tuple_element<Index, custom_tuple<Types...>>::type;

            static_assert(std::is_same_v<t_element, ct_element>, "custom_tuple and tuple have different types of elements");

            (std::any_cast<std::reference_wrapper<t_element>>(list_binding_args[Index])).get() = std::get<Index>(arg);
      }

#ifdef PRIVATE_TEST
      FRIEND_TEST(CustomTupleTest, DefaultCtor);
      FRIEND_TEST(CustomTupleTest, CopyCtor);
      FRIEND_TEST(CustomTupleTest, MoveCtor);
      FRIEND_TEST(CustomTupleTest, swap);
      FRIEND_TEST(CustomTupleTest, CopyAssignment);
      FRIEND_TEST(CustomTupleTest, MoveAssignment);
      FRIEND_TEST(CustomTupleTest, CustomCtor1);
      FRIEND_TEST(CustomTupleTest, TupleAssignment);
#endif
};

template <typename... Args>
auto custom_tie(Args&... args)
{
      return custom_tuple(args...);
}
