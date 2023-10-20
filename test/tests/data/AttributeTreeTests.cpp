#include <data/AttributeTree.hpp>
#include <gtest/gtest.h>

using cpm::data::AttributeTree;

struct NodeTests : public testing::Test
{
    AttributeTree::Node sut;
};

TEST_F(NodeTests, appendingChildrenCreatesNewSubnodes)
{
    sut.appendChild("one", 1);
    EXPECT_EQ(sut.getChildren().size(), 1);
    sut.appendChild("two", 2);
    EXPECT_EQ(sut.getChildren().size(), 2);
    EXPECT_EQ(sut.getChildren().at(0).getName(), "one");
    EXPECT_EQ(sut.getChildren().at(1).getName(), "two");
}