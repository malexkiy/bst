#include <BinarySearchTree.h>
#include <catch.hpp>
#include <sstream>

SCENARIO("bst init", "[init]") {
	BinarySearchTree<int> bst;

}

SCENARIO("bst insert", "[insert]") {
	BinarySearchTree<int> bst;

	bst.insertElement(8);
	bst.insertElement(3);
	bst.insertElement(10);

	std::stringstream ss;
	bst.inorderTraversal(ss);

	std::string str, pattern = "3 8 10 ";
	std::getline(ss, str);

	REQUIRE(str == pattern);
}

SCENARIO("bst in", "[in]") {
	BinarySearchTree<int> bst;

	bst.insertElement(8);
	bst.insertElement(3);
	bst.insertElement(10);

	std::stringstream ss;
	bst.preorderTraversal(ss);

	std::string str, pattern = "8 3 10 ";
	std::getline(ss, str);

	REQUIRE(str == pattern);
}

SCENARIO("bst pre", "[pre]") {
	BinarySearchTree<int> bst;

	bst.insertElement(8);
	bst.insertElement(3);
	bst.insertElement(10);

	std::stringstream ss;
	bst.postorderTraversal(ss);

	std::string str, pattern = "3 10 8 ";
	std::getline(ss, str);

	REQUIRE(str == pattern);
}

SCENARIO("bst post", "[post]") {
	BinarySearchTree<int> bst;

	bst.insertElement(8);
	bst.insertElement(3);
	bst.insertElement(10);

	REQUIRE(bst.findElement(8) == true);
	REQUIRE(bst.findElement(3) == true);
	REQUIRE(bst.findElement(10) == true);
	REQUIRE(bst.findElement(16) == false);
}

SCENARIO("bst delete", "[delete]") {
	BinarySearchTree<int> bst;

	bst.insertElement(8);
	bst.insertElement(3);
	bst.insertElement(10);

	bst.deleteElement(8);

	std::stringstream ss;
	bst.inorderTraversal(ss);

	std::string str, pattern = "3 10 ";
	std::getline(ss, str);

	REQUIRE(str == pattern);
}

SCENARIO("bst file write", "[write]") {
	BinarySearchTree<int> bst;
	std::ofstream p("test.bst");
	p << "3 3 8 10 ";
	p.close();

	std::ifstream in("test.bst");
	std::ofstream out("test.bst");

	bst.insertElement(8);
	bst.insertElement(3);
	bst.insertElement(10);

	out << bst;
	out.close();

	std::stringstream ss;
	bst.inorderTraversal(ss);

	std::string str, pattern = "3 3 8 10 ";
	std::getline(in, str);
	in.close();

	REQUIRE(str == pattern);
}

SCENARIO("bst file read", "[read]") {
	BinarySearchTree<int> bst;
	std::ofstream p("test.bst");
	p << "3 3 8 10 ";
	p.close();

	std::ifstream in("test.bst");

	in >> bst;

	std::stringstream ss;
	bst.inorderTraversal(ss);

	std::string str, pattern = "3 3 8 10 ";
	std::getline(in, str);
	in.close();

	REQUIRE(str == pattern);
}

SCENARIO("bst print", "[print]") {
	BinarySearchTree<int> bst;

	bst.insertElement(8);
	bst.insertElement(3);
	bst.insertElement(10);
	bst.insertElement(1);
	bst.insertElement(6);
	bst.insertElement(4);
	bst.insertElement(7);
	bst.insertElement(14);
	bst.insertElement(13);

	std::stringstream ss;
	ss << bst;

	std::string e, str, pattern = "8 3 10 1 6 14 4 7 13 ";
	
	while (!ss.eof())
	{
		std::getline(ss, e);
		str += e;
	}

	REQUIRE(str == pattern);
}

