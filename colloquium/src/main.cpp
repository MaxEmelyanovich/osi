#include "../include/form.h"
#include "../include/builder.h"
#include "../include/singleton.h"
#include "gtest/gtest.h"

TEST(CircleBuilderTest, createCircle) {
    CircleBuilder builder;
    Form* circle = builder.createForm();
    EXPECT_TRUE(circle != nullptr);
    EXPECT_TRUE(dynamic_cast<Circle*>(circle) != nullptr);
    delete circle;
}

TEST(SquareBuilderTest, createSquare) {
    SquareBuilder builder;
    Form* square = builder.createForm();
    EXPECT_TRUE(square != nullptr);
    EXPECT_TRUE(dynamic_cast<Square*>(square) != nullptr);
    delete square;
}

TEST(TriangleBuilderTest, createTriangle) {
    TriangleBuilder builder;
    Form* triangle = builder.createForm();
    EXPECT_TRUE(triangle != nullptr);
    EXPECT_TRUE(dynamic_cast<Triangle*>(triangle) != nullptr);
    delete triangle;
}

TEST(FormFactoryTest, createCircle) {
    CircleBuilder builder;
    FormFactory& factory = FormFactory::getInstance();
    factory.setBuilder(&builder);
    Form* circle = factory.createForm(CIRCLE);
    EXPECT_TRUE(circle != nullptr);
    EXPECT_TRUE(dynamic_cast<Circle*>(circle) != nullptr);
    delete circle;
}

TEST(FormFactoryTest, createSquare) {
    SquareBuilder builder;
    FormFactory& factory = FormFactory::getInstance();
    factory.setBuilder(&builder);
    Form* square = factory.createForm(SQUARE);
    EXPECT_TRUE(square != nullptr);
    EXPECT_TRUE(dynamic_cast<Square*>(square) != nullptr);
    delete square;
}

TEST(FormFactoryTest, createTriangle) {
    TriangleBuilder builder;
    FormFactory& factory = FormFactory::getInstance();
    factory.setBuilder(&builder);
    Form* triangle = factory.createForm(TRIANGLE);
    EXPECT_TRUE(triangle != nullptr);
    EXPECT_TRUE(dynamic_cast<Triangle*>(triangle) != nullptr);
    delete triangle;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}