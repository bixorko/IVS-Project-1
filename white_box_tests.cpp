//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     PETER VINARCIK <xvinar00@stud.fit.vutbr.cz>
// $Date:       $2019-01-03
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Peter Vinarcik
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

Matrix MatrixCreatorVector(int x, int y)
{
    Matrix matrix;
    matrix = Matrix(x, y);
    std::vector<std::vector< double > > values;
    for (int i = 0; i < x; i++){
        values.push_back(std::vector<double>());
        for (int j = 0; j < y; j++)
            values[i].push_back(j);
    }

    return matrix;
}

Matrix MatrixCreatorSpecValue(int x, int y, int add)
{
    Matrix matrix;
    matrix = Matrix(x, y);
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++){
            matrix.set(i,j,add);
        }

    return matrix;
}

TEST(MatrixCreatorPassed, ConstructTest)
{
ASSERT_NO_THROW(Matrix());
ASSERT_NO_THROW(Matrix(4,5));
ASSERT_NO_THROW(Matrix(28,5));
ASSERT_NO_THROW(Matrix(1,1));
ASSERT_NO_THROW(Matrix(596,289));
}

TEST(MatrixCreatorFailed, ConstructTest)
{
ASSERT_ANY_THROW(Matrix(0,9));
ASSERT_ANY_THROW(Matrix(0,0));
ASSERT_ANY_THROW(Matrix(18,0));
}

TEST(MatrixInitializationPassed, Values)
{
Matrix matrix;
matrix = Matrix(10,12);
EXPECT_TRUE(matrix.set(7,2,5));
EXPECT_TRUE(matrix.set(8,8,5));
EXPECT_TRUE(matrix.set(9,3,5));
EXPECT_TRUE(matrix.set(0,0,5));

matrix = Matrix(5,5);
EXPECT_TRUE(matrix.set(4,3,5));
EXPECT_TRUE(matrix.set(1,1,5));
EXPECT_TRUE(matrix.set(2,4,5));
EXPECT_TRUE(matrix.set(0,0,5));
}

TEST(MatrixInitializationFailed, Values)
{
Matrix matrix;
matrix = Matrix(9,9);
EXPECT_FALSE(matrix.set(-8,5,9));
EXPECT_FALSE(matrix.set(-3,5,15));
EXPECT_FALSE(matrix.set(5,-3,-19));
EXPECT_FALSE(matrix.set(5,-2,0));
EXPECT_FALSE(matrix.set(9,3,5));

matrix = Matrix(6,8);
EXPECT_FALSE(matrix.set(6,-3,9));
EXPECT_FALSE(matrix.set(6,9,15));
EXPECT_FALSE(matrix.set(5,12,-19));
}

TEST(PutArrayToMatrixPassed, Values)
{
Matrix matrix;
matrix = Matrix(5, 5);
std::vector<std::vector< double > > values;
for (int i = 0; i < 5; i++){
values.push_back(std::vector<double>());
for (int j = 0; j < 5; j++)
values[i].push_back(j);
}

EXPECT_TRUE(matrix.set(values));

matrix = Matrix(3, 7);
std::vector<std::vector< double > > values2;
for (int i = 0; i < 3; i++){
values2.push_back(std::vector<double>());
for (int j = 0; j < 7; j++)
values2[i].push_back(j);
}

EXPECT_TRUE(matrix.set(values2));
}

TEST(PutArrayToMatrixFailed, Values)
{
Matrix matrix;
matrix = Matrix(4, 8);
std::vector<std::vector< double > > values;
for (int i = 0; i < 5; i++){
values.push_back(std::vector<double>());
for (int j = 0; j < 5; j++)
values[i].push_back(j);
}

EXPECT_FALSE(matrix.set(values));
}

TEST(MatrixGetValuePassed, Values)
{
Matrix matrix;
matrix = MatrixCreatorSpecValue(6,6,0);
EXPECT_EQ(matrix.get(0,0),0);
matrix = MatrixCreatorSpecValue(2,4,23);
EXPECT_EQ(matrix.get(0,1),23);
matrix = MatrixCreatorSpecValue(6,9,17);
EXPECT_EQ(matrix.get(5,4),17);
}

TEST(MatrixGetValueFailed, Values)
{
Matrix matrix;
matrix = MatrixCreatorSpecValue(3,7,5);
EXPECT_ANY_THROW(matrix.get(5,8));
EXPECT_ANY_THROW(matrix.get(5,4));
EXPECT_ANY_THROW(matrix.get(-3,2));
EXPECT_ANY_THROW(matrix.get(8,3));
}

TEST(CompareTwoMatrixEqual, Values)
{
Matrix matrix, matrix2;
matrix = MatrixCreatorVector(5,5);
matrix2 = MatrixCreatorVector(5,5);
EXPECT_TRUE(matrix.operator==(matrix2));

matrix = MatrixCreatorVector(9,7);
matrix2 = MatrixCreatorVector(9,7);
EXPECT_TRUE(matrix.operator==(matrix2));
}

TEST(CompareTwoMatrixNonEqual, Values)
{
Matrix matrix, matrix2;
matrix = MatrixCreatorVector(18,6);
matrix2 = MatrixCreatorVector(4,12);
EXPECT_ANY_THROW(matrix.operator==(matrix2));

matrix = MatrixCreatorVector(23,19);
matrix2 = MatrixCreatorVector(19,23);
EXPECT_ANY_THROW(matrix.operator==(matrix2));

matrix = MatrixCreatorSpecValue(6,6,0);
matrix2 = MatrixCreatorSpecValue(6,6,4);
EXPECT_FALSE(matrix.operator==(matrix2));

matrix = MatrixCreatorSpecValue(16,23,156);
matrix2 = MatrixCreatorSpecValue(16,23,298);
EXPECT_FALSE(matrix.operator==(matrix2));
}

TEST(TwoMatrixPlus, Values)
{
Matrix matrix, matrix2, MatrixResult;
matrix = MatrixCreatorSpecValue(5,8,4);
matrix2 = MatrixCreatorSpecValue(5,8,7);
MatrixResult = MatrixCreatorSpecValue(5,8,11);
EXPECT_EQ(matrix.operator+(matrix2),MatrixResult);

matrix = MatrixCreatorSpecValue(9,9,6);
matrix2 = MatrixCreatorSpecValue(9,9,15);
MatrixResult = MatrixCreatorSpecValue(9,9,21);
EXPECT_EQ(matrix.operator+(matrix2),MatrixResult);
}

TEST(TwoMatrixPlusBadSize, Values)
{
Matrix matrix, matrix2, MatrixResult;
matrix = MatrixCreatorSpecValue(5,8,4);
matrix2 = MatrixCreatorSpecValue(5,9,7);
MatrixResult = MatrixCreatorSpecValue(5,8,11);
EXPECT_ANY_THROW(matrix.operator+(matrix2));

matrix = MatrixCreatorSpecValue(12,12,4);
matrix2 = MatrixCreatorSpecValue(8,8,7);
MatrixResult = MatrixCreatorSpecValue(8,8,11);
EXPECT_ANY_THROW(matrix.operator+(matrix2));
}

TEST(TwoMatrixPowerPassed, Values)
{
Matrix matrix, matrix2, ResultExp;
matrix = MatrixCreatorSpecValue(3,3,1);
matrix2 = MatrixCreatorSpecValue(3,3,2);
ResultExp = MatrixCreatorSpecValue(3,3,6);
EXPECT_EQ(ResultExp,  matrix.operator*(matrix2));

matrix = MatrixCreatorSpecValue(5,2,3);
matrix2 = MatrixCreatorSpecValue(2,2,3);
ResultExp = MatrixCreatorSpecValue(5,2,18);
EXPECT_EQ(ResultExp,  matrix.operator*(matrix2));
}

TEST(TwoMatrixPowerFailed, Values)
{
Matrix matrix, matrix2, ResultExp;
matrix = MatrixCreatorSpecValue(5,6,1);
matrix2 = MatrixCreatorSpecValue(5,6,2);
ResultExp = MatrixCreatorSpecValue(5,6,6);
EXPECT_ANY_THROW(matrix.operator*(matrix2));
}

TEST(MatrixPowerScalar, Values)
{
Matrix matrix, MatrixResult;
matrix = MatrixCreatorSpecValue(5,8,4);
MatrixResult = MatrixCreatorSpecValue(5,8,12);
EXPECT_EQ(matrix.operator*(3),MatrixResult);

matrix = MatrixCreatorSpecValue(3,3,5);
MatrixResult = MatrixCreatorSpecValue(3,3,20);
EXPECT_EQ(matrix.operator*(4),MatrixResult);
}

TEST(MatrixLinearSolvePassed, Values)
{
Matrix matrix;
matrix = Matrix(3,3);
matrix.set(0,0,3);
matrix.set(0,1,1);
matrix.set(0,2,1);
matrix.set(1,0,2);
matrix.set(1,1,2);
matrix.set(1,2,5);
matrix.set(2,0,1);
matrix.set(2,1,-3);
matrix.set(2,2,-4);
std::vector<double> values = {3,-1,2};
std::vector<double> res = {1,1,-1};
EXPECT_EQ(res, matrix.solveEquation(values));

matrix = Matrix(1,1);
matrix.set(0,0,1);
std::vector<double> values2 = {1};
std::vector<double> res2 = {1};
EXPECT_EQ(res2, matrix.solveEquation(values2));
}

TEST(MatrixLinearSolveFailed, Values)
{
Matrix matrix;
matrix = MatrixCreatorSpecValue(4,3,1);
std::vector<double> values = {1,2,3};
EXPECT_ANY_THROW(matrix.solveEquation(values));

matrix = MatrixCreatorSpecValue(4,4,1);
EXPECT_ANY_THROW(matrix.solveEquation(values));

matrix = MatrixCreatorSpecValue(3,3,1);
EXPECT_ANY_THROW(matrix.solveEquation(values));
}

/*** Konec souboru white_box_tests.cpp ***/
