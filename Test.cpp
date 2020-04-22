#include "doctest.h"
#include "FamilyTree.hpp"

using namespace family;
using namespace std;


TEST_CASE("Test creation of small input"){
	Tree T("Yosef");
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel");
	CHECK(T.relation("Yaakov") == "father");
	CHECK(T.relation("Rachel") == "mother");
	CHECK(T.find("father") == "Yaakov");
	CHECK(T.find("mother") == "Rachel");
}
TEST_CASE("Test creation bad input"){
	CHECK_THROWS_AS(Tree T(""), const exception&);
}

TEST_CASE("Test relation not found"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	CHECK(T.relation("Noah") == "unrelated");
	CHECK(T.relation("David") == "unrelated");
	CHECK(T.relation("Shlomo") == "unrelated");
	CHECK(T.relation("Yonah") == "unrelated");
	CHECK(T.relation("Yosef123") == "unrelated");
	CHECK(T.relation("1issaac") == "unrelated");
	CHECK(T.relation("avraham") == "unrelated");
	CHECK(T.relation("Te rah") == "unrelated");
} 

TEST_CASE("Test simple addition"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	 T.display();
	CHECK(T.relation("Yaakov") == "father");
	CHECK(T.relation("Rachel") == "mother");
	CHECK(T.relation("Isaac") == "grandfather");
	CHECK(T.relation("Rivka") == "grandmother");
	CHECK(T.relation("Avraham") == "great-grandfather");
	CHECK(T.relation("Terah") == "great-great-grandfather");
	//CHECK(T.relation("xyz") == "unrelated");
	CHECK(T.relation("Yosef") == "me"); 
}

TEST_CASE("Test ordered removal"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah")
	 .remove("Terah")
	 .remove("Avraham")
	 .remove("Rivka")
	 .remove("Isaac")
	 .remove("Rachel")
	 .remove("Yaakov");
	CHECK(T.relation("Yaakov") == "unrelated");
	CHECK(T.relation("Rachel") == "unrelated");
	CHECK(T.relation("Rivka") == "unrelated");
	CHECK(T.relation("Avraham") == "unrelated");
	CHECK(T.relation("Terah") == "unrelated");
	CHECK(T.relation("Yosef") == "me"); 
}
TEST_CASE("Test addition after removal"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah")
	 .remove("Terah")
	 .remove("Avraham")
	 .remove("Rivka")
	 .remove("Isaac")
	 .remove("Rachel")
	 .remove("Yaakov")
	 .addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	CHECK(T.relation("Yaakov") == "father");
	CHECK(T.relation("Rachel") == "mother");
	CHECK(T.relation("Isaac") == "grandfather");
	CHECK(T.relation("Rivka") == "grandmother");
	CHECK(T.relation("Avraham") == "great-grandfather");
	CHECK(T.relation("Terah") == "great-great-grandfather");
	CHECK(T.relation("Yosef") == "me"); 
}


TEST_CASE("Test root removal"){
	Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah")
	 .remove("Yosef");
	CHECK(T.relation("Yaakov") == "unrelated");
	CHECK(T.relation("Rachel") == "unrelated");
	CHECK(T.relation("Rivka") == "unrelated");
	CHECK(T.relation("Avraham") == "unrelated");
	CHECK(T.relation("Terah") == "unrelated");
	CHECK(T.relation("Yosef") == "unrelated"); 
}

TEST_CASE("Test unordered removal"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	 T.remove("Yaakov");
	CHECK(T.relation("Yaakov") == "unrelated");
	CHECK(T.relation("Rachel") == "mother");
	CHECK(T.relation("Isaac") == "unrelated");
	CHECK(T.relation("Rivka") == "unrelated");
	CHECK(T.relation("Avraham") == "unrelated");
	CHECK(T.relation("Terah") == "unrelated");
	CHECK(T.relation("Yosef") == "me");
}

TEST_CASE("Test duplicates"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Yaakov")
	 .addMother("Yaakov", "Rachel");
	CHECK(((T.relation("Yaakov") == "father") || (T.relation("Yaakov") == "grandfather")));
	CHECK(((T.relation("Rachel") == "mother") || (T.relation("Rachel") == "grandmother")));
}

TEST_CASE("Test unordered removal"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	T.remove("Yaakov");
	CHECK(T.relation("Yaakov") == "unrelated");
	CHECK(T.relation("Rachel") == "mother");
	CHECK(T.relation("Isaac") == "unrelated");
	CHECK(T.relation("Rivka") == "unrelated");
	CHECK(T.relation("Avraham") == "unrelated");
	CHECK(T.relation("Terah") == "unrelated");
	CHECK(T.relation("Yosef") == "me");
}

TEST_CASE("Test addittion after unordered removal"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	T.remove("Yaakov");
	CHECK(T.relation("Yaakov") == "unrelated");
	CHECK(T.relation("Rachel") == "mother");
	CHECK(T.relation("Isaac") == "unrelated");
	CHECK(T.relation("Rivka") == "unrelated");
	CHECK(T.relation("Avraham") == "unrelated");
	CHECK(T.relation("Terah") == "unrelated");
	CHECK(T.relation("Yosef") == "me");
	T.addFather("Yosef", "Yaakov") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	CHECK(T.relation("Yaakov") == "father");
	CHECK(T.relation("Rachel") == "mother");
	CHECK(T.relation("Isaac") == "grandfather");
	CHECK(T.relation("Rivka") == "grandmother");
	CHECK(T.relation("Avraham") == "great-grandfather");
	CHECK(T.relation("Terah") == "great-great-grandfather");
	CHECK(T.relation("Yosef") == "me"); 
	
}

TEST_CASE("Test find"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	CHECK(T.find("father") == "Yaakov");
	CHECK(T.find("mother") == "Rachel");
	CHECK(T.find("grandfather") == "Isaac");
	CHECK(T.find("grandmother") == "Rivka");
	CHECK(T.find("great-grandfather") == "Avraham");
	CHECK(T.find("great-great-grandfather") == "Terah");
	CHECK(T.find("me") == "Yosef"); 
}

TEST_CASE("Test not found"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka");
	CHECK(T.find("great-grandfather") == "not found");
	CHECK(T.find("great-great-grandfather") == "not found");
	T.remove("Rachel")
	 .remove("Yaakov");
	CHECK(T.find("mother") == "not found");
	CHECK(T.find("father") == "not found");
}
TEST_CASE("Test find bad input"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	CHECK_THROWS_AS(T.find("father1"), const exception&);
	CHECK_THROWS_AS(T.find("mother-2"), const exception&);
	CHECK_THROWS_AS(T.find("grandfather-great"), const exception&);
	CHECK_THROWS_AS(T.find("grand mother"), const exception&);
	CHECK_THROWS_AS(T.find("great grandfather"), const exception&);
	CHECK_THROWS_AS(T.find("mother-great-great-grandfather"), const exception&);
	CHECK_THROWS_AS(T.find("I"), const exception&); 
}
TEST_CASE("Test nmaes with spaces"){
    Tree T ("Yosef  "); 
	T.addFather("Yosef  ", "Yaak ov") 
	 .addMother("Yosef  ", " Rachel") 
	 .addFather("Yaak ov", "Isaac ")
	 .addMother("Yaak ov", " Rivka ")
	 .addFather("Isaac ", " A vraham")
	 .addFather(" A vraham", "Ter ah ");
	CHECK(T.relation("Yaak ov") == "father");
	CHECK(T.relation(" Rachel") == "mother");
	CHECK(T.relation("Isaac ") == "grandfather");
	CHECK(T.relation(" Rivka ") == "grandmother");
	CHECK(T.relation(" A vraham") == "great-grandfather");
	CHECK(T.relation("Ter ah ") == "great-great-grandfather");
	CHECK(T.relation("Yosef  ") == "me"); 
}
TEST_CASE("Test nmaes with non regular characters"){
    Tree T ("Yosef2"); 
	T.addFather("Yosef2", "Ya@kov") 
	 .addMother("Yosef2", "Rach3l") 
	 .addFather("Ya@kov", "$$$")
	 .addMother("Ya@kov", "Rivka!");
	CHECK(T.relation("Ya@kov") == "father");
	CHECK(T.relation("Rach3l") == "mother");
	CHECK(T.relation("%#!") == "unrelated");
	CHECK(T.relation("Rivka!") == "grandmother");
	CHECK(T.relation("Yosef2") == "me"); 
}

TEST_CASE("Test relation and find being inverse"){
    Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel") 
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	CHECK(T.relation(T.find("father")) == "father");
	CHECK(T.relation(T.find("mother")) == "mother");
	CHECK(T.relation(T.find("grandfather")) == "grandfather");
	CHECK(T.relation(T.find("grandmother")) == "grandmother");
	CHECK(T.relation(T.find("great-grandfather")) == "great-grandfather");
	CHECK(T.relation(T.find("great-great-grandfather")) == "great-great-grandfather");
	CHECK(T.find(T.relation("Yosef")) == "Yosef");
	CHECK(T.find(T.relation("Rachel")) == "Rachel");
	CHECK(T.find(T.relation("Yaakov")) == "Yaakov");
	CHECK(T.find(T.relation("Isaac")) == "Isaac");
	CHECK(T.find(T.relation("Avraham")) == "Avraham");
	CHECK(T.find(T.relation("Terah")) == "Terah");
}
