#include <data/AttributeTree.hpp>
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

using cpm::data::AttributeTree;

struct NodeTests : public testing::Test
{
    AttributeTree::Node sut;
};

TEST_F(NodeTests, appendingChildrenCreatesNewSubnodes)
{
    EXPECT_EQ(sut.getChildren().size(), 0);
    sut.appendChild("one", 1);
    EXPECT_EQ(sut.getChildren().size(), 1);
    sut.appendChild("two", 2);
    EXPECT_EQ(sut.getChildren().size(), 2);
    EXPECT_EQ(sut.getChildren().at(0).getName(), "one");
    EXPECT_EQ(sut.getChildren().at(1).getName(), "two");
}

TEST_F(NodeTests, userCanRetrieveValueOfNode)
{
    sut.setValue(1);
    EXPECT_EQ(sut.getValue<int>(), 1);
}

TEST_F(NodeTests, retrievingWrongValueTypeReturnsNullopt)
{
    sut.setValue(1);
    EXPECT_EQ(sut.getValue<std::string>(), std::nullopt);
}

TEST_F(NodeTests, retrievingMissingValueTypeReturnsNullopt)
{
    sut.appendChild("one");
    EXPECT_EQ(sut.getChildren().at(0).getValue<int>(), std::nullopt);
}

TEST_F(NodeTests, valuesOfChildrenCanBeSetAndRetrievedViaRoot)
{
    sut.appendChild("one", 1);
    EXPECT_EQ(sut.getChildren().at(0).getValue<int>(), 1);
    sut.getChildren().at(0).appendChild("two", 2);
    EXPECT_EQ(sut.getChildren().at(0).getChildren().at(0).getValue<int>(), 2);
}