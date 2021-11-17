#include "gepch.h"


glm::fvec4 getMat4Column(glm::mat4& toGet, int column)
{
	if (column > 3)
		throw "Incorrect index given in getMat4Column";
	return glm::fvec4(toGet[0][column], toGet[1][column], toGet[2][column], toGet[3][column]);
}

glm::mat4 setMat4Column(glm::mat4 matToSet, glm::fvec4& colToSet, int column)
{
	if (column > 3)
		throw "Incorrect index given in setMat4Column";
	matToSet[0][column] = colToSet[0];
	matToSet[1][column] = colToSet[1];
	matToSet[2][column] = colToSet[2];
	matToSet[3][column] = colToSet[3];
	return matToSet;
}

glm::fvec4 getMat4Row(glm::mat4& toGet, int row)
{
	if (row > 3)
		throw "Incorrect index given in getMat4Row";
	return glm::fvec4(toGet[row][0], toGet[row][1], toGet[row][2], toGet[row][3]);
}

glm::mat4 setMat4Row(glm::mat4 matToSet, glm::fvec4& rowToSet, int row)
{
	if (row > 3)
		throw "Incorrect index given in getMat4Row";
	matToSet[row][0] = rowToSet[0];
	matToSet[row][1] = rowToSet[1];
	matToSet[row][2] = rowToSet[2];
	matToSet[row][3] = rowToSet[3];
	return matToSet;
}
