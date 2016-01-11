//******************************************************************************
//This class stores an image as a list of points and a list of edges between
//those points.
//
//Samuel Kinnett, 2016
//******************************************************************************

#ifndef VECTOR_IMAGE_H
#define VECTOR_IMAGE_H

#include <vector>
#include "vector2D.h"

struct VectorImage {

	public:
		//The points vector stores a list of vectors describing the
		//points of the image.
		std::vector<Vector2D*> 	points;

		//The edges vector stores a list of integers referring to the
		//indexes of the points making up the image. When being drawn,
		//the image begins at the first point in the edges list which 
		//is then connected to each subsequent point in the edges list
		//unless it reaches a '-1'. In this case, a new continuous line
		//will begin starting from the point immediately following the 
		//-1. In this way, a single image can have multiple seperate
		//sections.
		std::vector<int>	edges;
};

#endif
