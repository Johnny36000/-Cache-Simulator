#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<cmath>
#include<bitset>
#include<string>
#include"global.h"
using namespace std;

struct value 
{
	string tag="0";
	bool valid_bit = 0;
	vector<string> data;
};

class cache
{
public: 

	static cache& getinstance(int size = 0, int line_size = 0,int cache_access=0);
	cache(const cache&) = delete;
	static void move(string address) { getinstance().move_block(address);}
	static void print() { getinstance().Iprint(); }
	static bool Search(string address) { 
		return getinstance().search(address); }

private: 
	cache(int size, int line_size,int cache);
	cache(){}
	void create_cache();
	map<string, value> CA;
	map<int, vector<int>> Memory;
	void move_block(string address);
	void Iprint();
	bool search(string address);
	int size = 0;   //cache size
	int line_size = 0; // block size
	int no_blocks = 0;
	int index_size = 0;
	int tag_size = 0;
	float hit = 0;
	float miss = 0;
	int offset = 0;
	float access_times = 0;
	int cache_time = 0;
	int AMAT();
	int cahce_entry = 0;
	
	
	
};

