#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <cmath>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/foreach.hpp>


using namespace std;
using namespace boost::algorithm;

struct Node
{
	double x;
	double y;
	long long refs; // falls > 1 bekommt es eine Kreuzung
};

map<long long, Node> nodes;
typedef map<long long, Node>::value_type NodesVal;
typedef map<long long, Node>::iterator NodesIt;

struct Way
{
	list<long long> nodes;
	string name;
};
typedef list<long long>::iterator WayNodesIt;

map<long long, Way> ways;
typedef map<long long, Way>::value_type WaysVal;
typedef map<long long, Way>::iterator WaysIt;
long long ways_min_id = 1;

static bool IsQuotMark(char c) {return c == '"';};
static bool IsLessThanSign(char c) {return c == '<';};

// diese Funktion muss für jedes Zielgebiet angepasst werden;
static Node Transform(double lon, double lat)
{
	Node out = {
		1000 + 16000 *(lon -6.08479),
		1000 - 27000 *(lat  -50.77466),
		/*500 + 24000 *(lon -7.1809),
		500 - 40500 *(lat  -50.1513),*/
		0
	};
	return out;
};

// Kilometer pro Pixelabstand
static const double scale = 0.004;

static void InsertNode(const string& line)
{
	//cout << line << endl;
	list<string> tokens;
	split(tokens, line, IsQuotMark);
	long long id = -1;
	double lon = 500;
	double lat = 500;
	enum {
		NOTHING,
		ID,
		LON,
		LAT
	} next_val = NOTHING;
	BOOST_FOREACH(string& token, tokens){
		trim(token);
		if(next_val != NOTHING){
			// vorhin wurde das attribut gefunden,
			// jetzt wird der wert zugewiesen
			istringstream token_stream(token);
			switch(next_val){
			case ID:
				token_stream >> id;
				break;
			case LON:
				token_stream >> lon;
				break;
			case LAT:
				token_stream >> lat;
				break;
			};
			next_val = NOTHING;
		}
		// suche nach passenden attributen
		else if(token == "id="){
			next_val = ID;
		}
		else if(token == "lon="){
			next_val = LON;
		}
		else if(token == "lat="){
			next_val = LAT;
		}
		else {
			//cout << "?? (" << token << ")\t";
		};
	};
	//cout << id << " = " << lon << ',' << lat << endl;
	Node node = Transform(lon, lat);
	if(
		node.y < 1 || node.y > 1950 
		|| node.x < 1 || node.x > 1950 
	) return;
	nodes.insert(NodesVal(id, node));
	//cerr << "x=" <<  node.x << " y=" << node.y << "\n";
	//cout << "<div style=\"position: absolute; border: 1px solid brown; width: 2px; height: 2px; left:" << floor(xy.x) << "px; top:" << floor(xy.y) << "px;\"></div>\n";
};

static bool UsefullTag(const string& tag)
{
	if(tag.find("k=\"highway\"") == string::npos) return false;
	if(tag.find("motorway") != string::npos) return true;
	if(tag.find("motorway_link") != string::npos) return true;
	if(tag.find("trunk") != string::npos) return true;
	if(tag.find("trunk_link") != string::npos) return true;
	if(tag.find("primary") != string::npos) return true;
	if(tag.find("primary_link") != string::npos) return true;
	if(tag.find("secondary") != string::npos) return true;
	if(tag.find("tertiary") != string::npos) return true;
	if(tag.find("secondary_link") != string::npos) return true;
	if(tag.find("residential") != string::npos) return true;
	if(tag.find("unclassified") != string::npos) return true;
	return false;
};

static string ConvertName(const string& input){
	string name = input + "_______";
	for(int i=0; i<name.size(); ++i){
		unsigned char c = name[i];
		unsigned char d = ' '; // wird nächster buchstabe
		if(c >= 'a' && c <= 'z') continue;
		if(c >= 'A' && c <= 'Z') continue;
		if(c >= '0' && c <= '9') continue;
		switch(c){ // UTF-8 ersetzen quick+dirty
		case 0xc3: // high 'ü','ä','ö','ß'
			if(i+1 < name.size()) d = name[i+1];
			c = (d == 0xbc)? 'u':'_'; 
			c = (d == 0xb6)? 'o':c; 
			c = (d == 0xa4)? 'a':c; 
			c = (d == 0x9f)? 's':c; 
			break; 
		case 0x9f: c = 's'; break; // low 'ß'
		case 0xbc: // low 'ü'
		case 0xb6: // low 'ö'
		case 0xa4: c = 'e'; break;// low 'ä'
		default: c = '_';
		};
		name[i] = c;
	};
	return string(name, 0, 5);
};

static void GetName(string line, string& name){
	if(line.find("k=\"name\"") != string::npos){
		size_t begin = line.find("v=\"") + 3;
		if(begin == string::npos) return;
		istringstream node_iss(string(line, begin));
		getline(node_iss, name, '"');
		name = ConvertName(name);
	};
	if(line.find("k=\"ref\"") != string::npos && name == "Weg"){
		size_t begin = line.find("v=\"") + 3;
		if(begin == string::npos) return;
		istringstream node_iss(string(line, begin));
		getline(node_iss, name, '"');
		name = ConvertName(name);
	};
};

static void InsertWay(const string& input){
	list<string> lines;
	split(lines, input, IsLessThanSign);
	// id herausfinden
	long long id = -1;
	{
		string& header = *(lines.begin());
		list<string> tokens;
		split(tokens, header, IsQuotMark);
		bool next_val = false;
		BOOST_FOREACH(string& token, tokens){
			trim(token);
			if(next_val){
				istringstream token_stream(token);
				token_stream >> id;
				break;
			}
			if(token == "id=") next_val = true;
		};
	};
	//cout << "id=" << id << endl;
	lines.pop_front();
	lines.pop_back();
	// nodes und tags
	bool usefull_as_street = false;
	Way way;
	way.name = "Weg";
	typedef list<long long>::iterator WayNodesIt;
	BOOST_FOREACH(string& line, lines){
		trim(line);
		if(line.find("nd ") == 0){
			size_t begin = line.find("ref=\"") + 5;
			if(begin == string::npos) continue;
			istringstream node_iss(string(line, begin));
			long long node;
			node_iss >> node;
			//cout << line << " -> ";
			//cout << node << "\t";
			if(nodes.find(node) != nodes.end())
			way.nodes.push_back(node);
		}
		else if(line.find("tag ") == 0){
			usefull_as_street |= UsefullTag(line);
			GetName(line, way.name);
		};
	};
	// straße oder nicht?
	if(!usefull_as_street) return;
	// keine Straßen außerhalb.
	if(way.nodes.size() < 2) return;
	// einfügen
	ways.insert(WaysVal(id, way));
	if(id < ways_min_id) ways_min_id = id;
	// anfang und ende sind immer kreuzungen
	++(nodes[way.nodes.front()].refs);
	++(nodes[way.nodes.back()].refs);
	// alle eins hoch
	for(
		WayNodesIt it = way.nodes.begin();
		it != way.nodes.end();
		++it
	){
		++(nodes[*it].refs);	
	};
};

int main()
{
	string line;
	long long roundtrips = 0;
	cerr << "Einlesen...\n";
	while(cin.good()){
		++roundtrips;
		getline(cin, line, '>');
		if(line.find("<node") != string::npos){
			InsertNode(string(line, 8));
		}
		else if(line.find("<way") != string::npos){
			string waylines = line;
			while(
				cin.good()
				&& line.find("</way") == string::npos
			){
				getline(cin, line, '>');
				waylines += line;
			};
			InsertWay(string(waylines, 7));
		};
		if((roundtrips & 0xFFFF) == 0){
			cerr << "Zwischenstand: ";
			cerr << nodes.size() << " Knoten, ";
			cerr << ways.size() << " Straßen" << endl;
			//if(roundtrips > 200000) return 0;
		};
	};
	// Kreuzungs-Ausgabe
	cerr << "Ausgabe der Kreuzungen...\n";
	for(
		NodesIt it = nodes.begin();
		it != nodes.end();
		++it
	){
		if(it->second.refs > 1 && it->second.x != 0){
			cout << "KREUZUNG Kr" << it->first;
			cout << ' ' << int(round(it->second.refs));
			cout << ' ' << int(round(it->second.x));
			cout << ' ' <<  int(round(it->second.y)) << endl;
		};
	};
	// Straßen segmentieren. An Kreuzungen werden Wege aufgespalten.
	cerr << "Straßen segmentieren... ";
	for(
		WaysIt it = ways.begin();
		it != ways.end();
		++it		
	){
		Way& way = it->second;
		for(
			WayNodesIt it2 = way.nodes.begin();
			it2 != way.nodes.end();
			++it2
		){
			if(nodes[*it2].refs > 1){
				Way spliced_off;
				spliced_off.name = way.name;
				spliced_off.nodes.splice(
					spliced_off.nodes.end(),
					way.nodes,
					way.nodes.begin(),
					it2
				);
				spliced_off.nodes.push_back(*it2);
				ways.insert(WaysVal(
					--ways_min_id,
					spliced_off
				));
			}
		};
	};
	cerr << "Jetzt " << ways.size() << "Straßen\n";
	// Straßen-Ausgabe
	cerr << "Ausgabe der Straßen...\n";
	int count_up = 1;
	for(
		WaysIt it = ways.begin();
		it != ways.end();
		++it		
	){
		// artefakte vom segmentieren auslassen.
		if(it->second.nodes.size() < 2) continue;
		cout << "STRASSE";
		cout << " Kr"  << it->second.nodes.front();
		cout << " Kr"  << it->second.nodes.back();
		cout << ' ' << it->second.name << ++count_up;
		cout << ' ' << it->second.name << ++count_up;
		// Länge berechnen
		double length = 0;
		Node prev_node = nodes[it->second.nodes.front()];
		BOOST_FOREACH(long long node_id, it->second.nodes){
			Node& node = nodes[node_id];
			double delta_x = node.x - prev_node.x;
			double delta_y = node.y - prev_node.y;
			length += scale * sqrt(
				delta_x * delta_x
				+ delta_y * delta_y
			);
		};
		cout << ' ' << length;
		cout << ' ' << it->second.nodes.size();
		BOOST_FOREACH(long long node_id, it->second.nodes){
			Node& node = nodes[node_id];
			cout << ' ' << int(round(node.x));
			cout << ' ' << int(round(node.y));
		};
		cout << endl;
	};
	cout << endl;
	return 0;
};
