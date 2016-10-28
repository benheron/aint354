#pragma once
#include "../Vec2.h";
#include <vector>

class Graph {

	struct node {
		Vec2 pos;
		std::vector<Vec2> dirs;
		//std::string iD;
		
	};

public:
	/**
	@brief Create the graph
	**/
	Graph();
	~Graph();

private:


};