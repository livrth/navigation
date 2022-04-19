#include "model.h"
using namespace std;

Model::Model(string name) : name{name} {
}
void Model::set_id(Id id) {
	this->id = id;
}
Id Model::get_id() {
	return this->id;
}
void Model::set_name(string name) {
	this->name = name;
}
string Model::get_name() {
	return this->name;
}