//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     PETER VINARCIK <xvinar00@stud.fit.vutbr.cz>
// $Date:       $2019-01-03
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Peter Vinarcik
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for(int i = 0; i < 9; i++)
            btree.InsertNode(values[i]);
    }
    BinaryTree btree;
};

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree btree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for(int i = 0; i < 9; i++)
            btree.InsertNode(values[i]);
    }
    BinaryTree btree;
};

TEST_F(EmptyTree, InsertNode)
{
std::pair<bool, Node_t *> expect;
expect = btree.InsertNode(18);
EXPECT_TRUE(expect.first);
}

TEST_F(NonEmptyTree, InsertNode)
{
std::pair<bool, Node_t *> expect;
std::pair<bool, Node_t *> compare;
compare = btree.InsertNode(9);
expect = btree.InsertNode(5);
EXPECT_FALSE(expect.first);
expect = btree.InsertNode(9);
EXPECT_FALSE(expect.first);
EXPECT_EQ(compare.second, expect.second);
expect = btree.InsertNode(12);
EXPECT_TRUE(expect.first);
}

TEST_F(EmptyTree, DeleteNode)
{
EXPECT_FALSE(btree.DeleteNode(5));
EXPECT_FALSE(btree.DeleteNode(-6));
EXPECT_FALSE(btree.DeleteNode(2));
EXPECT_FALSE(btree.DeleteNode(1));
}

TEST_F(NonEmptyTree, DeleteNode)
{
EXPECT_TRUE(btree.DeleteNode(1));
EXPECT_TRUE(btree.DeleteNode(5));
EXPECT_FALSE(btree.DeleteNode(15));
EXPECT_FALSE(btree.DeleteNode(10));
}

TEST_F(EmptyTree, FindNode)
{
EXPECT_EQ(NULL, btree.FindNode(673));
EXPECT_EQ(NULL, btree.FindNode(-6));
EXPECT_EQ(NULL, btree.FindNode(6));
EXPECT_EQ(NULL, btree.FindNode(5));
}

TEST_F(NonEmptyTree, FindNode)
{
EXPECT_EQ(NULL, btree.FindNode(17));
EXPECT_EQ(NULL, btree.FindNode(11));
EXPECT_EQ(NULL, btree.FindNode(-5));
}

TEST_F(TreeAxioms, Axiom1)
{
std::vector<Node_t *> outLeafNodes;
btree.GetLeafNodes(outLeafNodes);
EXPECT_TRUE(BinaryTree::BLACK == outLeafNodes[0]->color && BinaryTree::BLACK == outLeafNodes[4]->color);
}

TEST_F(TreeAxioms, Axiom2)
{
std::vector<Node_t *> outAllNodes;
btree.GetAllNodes(outAllNodes);
int i = 0;
while (outAllNodes[i]->color != BinaryTree::RED){
i++;
}
EXPECT_TRUE(outAllNodes[i]->pRight->color == BinaryTree::BLACK && outAllNodes[i]->pLeft->color == BinaryTree::BLACK);
}

TEST_F(NonEmptyTree, RootTest)
{
EXPECT_EQ(btree.GetRoot()->key, 4);
}

/*** Konec souboru black_box_tests.cpp ***/
