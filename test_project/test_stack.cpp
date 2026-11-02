#include "../mp2-lab3-stack/Stack.h"

#include "gtest.h"

TEST(Stack, can_create_stack_with_positive_length) {
	ASSERT_NO_THROW(Stack<char> st(3));
}

//Могу, не могу создать, тесты для добавления и удаления элемента (могу добавить, могу вынуть - 
// и проверить вершину стека), копирование и присваивание, тесты на пустоту и полноту (не могу извлечь из пустого, 
// не могу добавить в полный), нагрузочный тест (созддается столько, сколько было заявлено)

//Создать новый проект, но теперь выбираем не пустой проект, а проект, который называется Google Test

TEST(Stack, throws_when_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(Stack<int> st(-3));
}

TEST(Stack, can_get_size) {
	Stack<int> a(5);
	EXPECT_EQ(5, a.getSize());
}

TEST(Stack, can_get_topid) {
	Stack<int> a(5);
	EXPECT_EQ(-1, a.getTopId());
}

TEST(Stack, can_create_copied_vector) {
	Stack<int> a(10);
	ASSERT_NO_THROW(Stack<int> b(a));
}

TEST(Stack, copied_stack_is_equal_to_source_one) {
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	Stack<int> b(a);
	EXPECT_EQ(a, b);
}

TEST(Stack, copied_stack_has_its_own_memory) {
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	Stack<int> b(a);
	a.pop();
	a.push(100);
	ASSERT_TRUE(4 == b.pop());
}

TEST(Stack, can_push_and_pop_element){
	Stack<int> st(5);
	st.push(10);
	EXPECT_EQ(10, st.pop());
}

TEST(Stack, can_assign_vector_to_itself){
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	ASSERT_NO_THROW(a = a);
	for (int i = 4; i >= 0; i--) {
		EXPECT_EQ(i, a.pop());
	}
}

TEST(Stack, can_assign_stack_with_equal_size) {
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	Stack<int> b(5);
	for (int i = 0; i < 3; i++) {
		b.push(i);
	}
	a = b;
	ASSERT_NO_THROW(a == b);
}

TEST(Stack, assign_operator_change_stack_size) {
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	Stack<int> b(3);
	for (int i = 0; i < 3; i++) {
		b.push(i);
	}
	b = a;
	EXPECT_EQ(5, b.getSize());
}

TEST(Stack, can_assign_stack_of_different_size) {
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	Stack<int> b(3);
	for (int i = 0; i < 3; i++) {
		b.push(i);
	}
	ASSERT_NO_THROW(b = a);
}

TEST(Stack, compare_equal_stack_return_true) {
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	Stack<int> b(5);
	for (int i = 0; i < 5; i++) {
		b.push(i);
	}
	ASSERT_TRUE(a == b);
}

TEST(Stack, compare_stack_with_itself_return_true){
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	ASSERT_TRUE(a == a);
}

TEST(Stack, stacks_with_different_size_are_not_equal){
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	Stack<int> b(3);
	for (int i = 0; i < 3; i++) {
		b.push(i);
	}
	ASSERT_FALSE(a == b);
}

TEST(Stack, empty_stack_after_delete_last_element) {
	Stack<int> a(5);
	a.push(10);
	a.pop();
	ASSERT_TRUE(a.IsEmpty());
}

TEST(Stack, stack_is_full_after_filling) {
	Stack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.push(i);
	}
	ASSERT_TRUE(a.IsFull());
}

TEST(Stack, can_completely_fill_and_completely_clean) {
	Stack<int> a(10);
	for (int i = 0; i < 10; i++) {
		a.push(i);
	}
	EXPECT_EQ(true, a.IsFull());
	for (int i = 10; i >= 1; i--) {
		a.pop();
	}
	EXPECT_EQ(true, a.IsEmpty());
}