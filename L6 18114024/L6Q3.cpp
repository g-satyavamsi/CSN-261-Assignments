/**
 * @file L6Q3.cpp
 * G.Satya Vamsi
 * @brief Bentley-Ottmann Algorithm
 * @date Oct 08,2019
 * 
 */
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

int origin_pt=0,ending_pt=1;

struct Pt{
	char letter;
	double x_coord, y_coord;
	Pt & operator = (Pt const & b) { letter = b.letter;  x_coord = b.x_coord; y_coord = b.y_coord; return *this; }
	Pt(const Pt & b) : letter(b.letter), x_coord(b.x_coord), y_coord(b.y_coord) {}
	Pt(char _letter, double _x_coord, double _y) : letter(_letter), x_coord(_x_coord), y_coord(_y) {}
	bool operator <(const Pt & b) const
	{
		if (y_coord < b.y_coord - 1.0e-9) return true;
		else if (y_coord > b.y_coord + 1.0e-9) return false;
		else if (x_coord < b.x_coord - 1.0e-9) return true;
		else return false;
	}
	bool operator ==(const Pt & b) const
	{
		return fabs(y_coord - b.y_coord) < 1.0e-9 && fabs(x_coord - b.x_coord) < 1.0e-9;
	}
	bool operator !=(const Pt & b) const
	{
		return fabs(y_coord - b.y_coord) > 1.0e-9 || fabs(x_coord - b.x_coord) > 1.0e-9;
	}
};

struct Line
{
	Pt beg, end;
	Line & operator = (Line const & b) { beg = b.beg; end = b.end; return *this; }
	Line(const Line & b) : beg(b.beg), end(b.end) {}
	Line(const Pt & _beg, const Pt & _end) : beg(_beg), end(_end) {}
};

class event_less
{
public:
	bool operator()(const pair<double, int> & a, const pair<double, int> & b) const
	{
		if (a.first < b.first - 1.0e-9)
			return true;
		else if (a.first > b.first + 1.0e-9)
			return false;
		else if (a.second < b.second)
			return true;
		return false;
	}
};

pair<bool, Pt> intersect(const Line & a, const Line & b, bool print)
{
	Pt ret('a', 0, 0);
	double div = (a.beg.x_coord - a.end.x_coord)*(b.beg.y_coord - b.end.y_coord) - (a.beg.y_coord - a.end.y_coord)*(b.beg.x_coord - b.end.x_coord), t;
	if (fabs(div) < 1.0e-13)
	{
		if (print) cout << "divisor is zero" << endl;
		    return make_pair(false, ret);
	}
	ret.x_coord = ((a.beg.x_coord*a.end.y_coord - a.beg.y_coord*a.end.x_coord)*(b.beg.x_coord - b.end.x_coord) - (a.beg.x_coord - a.end.x_coord)*(b.beg.x_coord*b.end.y_coord - b.beg.y_coord*b.end.x_coord)) / div;
	ret.y_coord = ((a.beg.x_coord*a.end.y_coord - a.beg.y_coord*a.end.x_coord)*(b.beg.y_coord - b.end.y_coord) - (a.beg.y_coord - a.end.y_coord)*(b.beg.x_coord*b.end.y_coord - b.beg.y_coord*b.end.x_coord)) / div;
	if (print) cout << "found (" << ret.x_coord << "," << ret.y_coord << ")" << endl;
	if (fabs(a.end.x_coord - a.beg.x_coord) > 1.0e-9)
	{
		t = (ret.x_coord - a.beg.x_coord) / (a.end.x_coord - a.beg.x_coord);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9){ 
            if (print) cout << "out of bound: " << t << endl; 
                return make_pair(false, ret); 
        }
	}
	if (fabs(a.end.y_coord - a.beg.y_coord) > 1.0e-9)
	{
		t = (ret.y_coord - a.beg.y_coord) / (a.end.y_coord - a.beg.y_coord);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9){ 
            if (print) cout << "out of bound: " << t << endl; 
                return make_pair(false, ret); 
        }
	}
	if (fabs(b.end.x_coord - b.beg.x_coord) > 1.0e-9)
	{
		t = (ret.x_coord - b.beg.x_coord) / (b.end.x_coord - b.beg.x_coord);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { 
            if (print) cout << "out of bound: " << t << endl; 
                return make_pair(false, ret); 
        }
	}
	if (fabs(b.end.y_coord - b.beg.y_coord) > 1.0e-9)
	{
		t = (ret.y_coord - b.beg.y_coord) / (b.end.y_coord - b.beg.y_coord);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9){ 
            if (print) cout << "out of bound: " << t << endl; 
                return make_pair(false, ret); 
        }
	}
	if (print) cout << "intersection accepted" <<endl;
	    return make_pair(true, ret);
}

void intersect(int a, int b, const Pt & I, vector<Line> & lines, multimap<Pt, int> & sweep, multimap<pair<double,int>, int,event_less> & events, bool print)
{
	
	{
		int rem_end_events[2];
		rem_end_events[0] = a;
		rem_end_events[1] = b;
		for (int k = 0; k < 2; ++k){
			pair< multimap<pair<double,int>, int,event_less>::iterator, multimap<pair<double,int>,int,event_less>::iterator > del = events.equal_range(make_pair(lines[rem_end_events[k]].end.x_coord,ending_pt)); //get all events at position of the end
			bool flag = false;
			for (multimap<pair<double,int>, int,event_less>::iterator it = del.first; it != del.second; ++it){
				if (it->first.second == ending_pt && it->second == rem_end_events[k]){
					events.erase(it);
					flag = true;
					break;
				}
			}
			if (!flag) cout << "Cannot find proper ending event for Line" << endl;
		}
	}
	lines.push_back(Line(I, lines[a].end));
	events.insert(make_pair(make_pair(I.x_coord,origin_pt), (int)lines.size() - 1));
	events.insert(make_pair(make_pair(lines.back().end.x_coord,ending_pt),(int)lines.size() - 1));
	lines[a].end = I;
	events.insert(make_pair(make_pair(I.x_coord,ending_pt), a));
	lines.push_back(Line(I, lines[b].end));
	events.insert(make_pair(make_pair(I.x_coord,origin_pt), (int)lines.size() - 1));
	events.insert(make_pair(make_pair(lines.back().end.x_coord,ending_pt), (int)lines.size() - 1));
	lines[b].end = I;
	events.insert(make_pair(make_pair(I.x_coord,ending_pt), b));
	if (print){
		cout << "Number of events: " << events.size() << endl;
		for (multimap<pair<double, int>, int,event_less>::iterator it = events.begin(); it != events.end(); ++it)
			cout << "x_coord: " << it->first.first << " type " << (it->first.second == origin_pt ? "start" : "end") << " Line " << it->second << endl;
	}
}


void intersect(vector<Line> & lines, vector<Pt> & intersections, bool print)
{
	multimap<pair<double,int>,int,event_less> events;
	multimap<Pt,int> sweep;
	
	if( print )
	{
		cout << "Input lines[" << lines.size() << "]: " << endl;
		for (vector<Line>::iterator it = lines.begin(); it != lines.end(); ++it)
			cout << "[ " << it->beg.letter << "(" << it->beg.x_coord << "," << it->beg.y_coord << "), " << it->end.letter << "(" << it->end.x_coord << "," << it->end.y_coord << ") ] " << endl;
		cout << "Create events based on lines." << endl;
	}

	for (int k = 0; k < (int)lines.size(); ++k){
		if (lines[k].beg.x_coord > lines[k].end.x_coord)
			swap(lines[k].beg, lines[k].end);
		events.insert(make_pair(make_pair(lines[k].beg.x_coord,origin_pt),k));
		events.insert(make_pair(make_pair(lines[k].end.x_coord,ending_pt), k));
	}


	if (print){
		cout << "Number of events: " << events.size() << endl;
		for (multimap<pair<double, int>, int,event_less>::iterator it = events.begin(); it != events.end(); ++it)
			cout << "x_coord: " << it->first.first << " type " << (it->first.second == origin_pt ? "start" : "end") << " Line " << it->second << endl;
		
		cout << " Start parsing events" << endl;
	}
	
	while (!events.empty()){
		multimap<pair<double,int>,int,event_less>::iterator first = events.begin();
		int t = first->first.second;
		int s = first->second;
		events.erase(first);
		if (t == origin_pt){
			if( print ) cout << "Line " << s << " start" << endl;
			
			multimap<Pt, int>::iterator ins = sweep.insert(make_pair(lines[s].beg, s));
			if (print){
				cout << "Inserted into sweep" << endl;
				for (multimap<Pt, int>::iterator it = sweep.begin(); it != sweep.end(); ++it)
					cout << it->first.letter << "(" << it->first.x_coord << "," << it->first.y_coord << ")" << " Line " << it->second << endl;
			}
			
			for (int dir = 0; dir <= 1; ++dir)
			{
				if( print ) cout << "Looking " << (dir ? "up" : "down") << endl;
				multimap<Pt, int>::iterator iter = ins;
				while ((dir ? ++iter : iter--) != (dir ? sweep.end() : sweep.begin())){
					if (print) 
                        cout << "test " << s << " with " << iter->second << endl;
					if (lines[s].beg != lines[iter->second].beg) {
						if (print) cout << "checking intersection" << endl;
						pair<bool, Pt> I = intersect(lines[s], lines[iter->second],print);
						if (I.first){
							I.second.letter += (char)intersections.size();
							if( print ) cout << "Intersection of " << s << " and " << iter->second << " at " << I.second.letter << "(" << I.second.x_coord << "," << I.second.y_coord << ")" << endl;
							intersections.push_back(I.second);
							intersect(s, iter->second, I.second, lines, sweep, events,print);
						}
					}
					else if (print) cout << "skipping lines with same starting Pt" << endl;
					if ((2*dir-1)*(iter->first.y_coord - ins->first.y_coord) > 0) 
						break;
				}
			}
		}
		else if (t == ending_pt)
		{
			if( print ) 
                cout << "Line " << s << " end" << endl;
			pair< multimap<Pt, int>::iterator, multimap<Pt, int>::iterator > range = sweep.equal_range(lines[s].beg);
			if( print ) 
                cout << "Range distance " << distance(range.first,range.second) << " sweep size " << sweep.size() << endl;
			multimap<Pt, int>::iterator above = range.second, below = range.first;
			bool flag = false, test = true;
			if( below-- == sweep.begin() ) 
                test = false;
			if( above == sweep.end() ) 
                test = false;
			if( test && print ) 
            cout << "Test will be performed" << endl;
			for (multimap<Pt, int>::iterator it = range.first; it != range.second; ++it) {
				if( it->second == s) {
					if (print){
						cout << "Erase Line " << s << " from sweep: " << endl;
						for (multimap<Pt, int>::iterator it = sweep.begin(); it != sweep.end(); ++it)
							cout << it->first.letter << "(" << it->first.x_coord << "," << it->first.y_coord << ")" << " Line " << it->second << endl;
					}
					sweep.erase(it);
					flag = true;
					break; 
				}
			}
			if (!flag) 
                cout << __FILE__ << ":" << __LINE__ <<  " Error: cannot find Line " << s << " in sweep" << endl;
			if (test){
				if (print) cout << "test " << below->second << " with " << above->second << endl;
				if (lines[above->second].beg != lines[below->second].beg){
					if (print) cout << "checking intersection" << endl;
					pair<bool, Pt> I = intersect(lines[below->second], lines[above->second],print);
					if (I.first){
						I.second.letter += (char)intersections.size();
						if( print ) 
                            cout << "Intersection of " << below->second << " and " << above->second << " at " << I.second.letter << "(" << I.second.x_coord << "," << I.second.y_coord << ")" << endl;
						intersections.push_back(I.second);
						intersect(below->second, above->second, I.second, lines, sweep, events,print);
					}
				}
				else if (print) cout << "skipping lines with same starting Pt" << endl;
			}
		}
	}
	
}

void linearfitline(double x_coord[],double y_coord[],int n){
	int i;
	double a,b;
    double x_coordsum=0,x_coord2sum=0,ysum=0,x_coordysum=0; 
    for (i=0;i<n;i++){
        x_coordsum=x_coordsum+x_coord[i];                   
        ysum=ysum+y_coord[i];                       
        x_coord2sum=x_coord2sum+pow(x_coord[i],2);      
        x_coordysum=x_coordysum+x_coord[i]*y_coord[i];  
    }
    a=(n*x_coordysum-x_coordsum*ysum)/(n*x_coord2sum-x_coordsum*x_coordsum);  
    b=(x_coord2sum*ysum-x_coordsum*x_coordysum)/(x_coord2sum*n-x_coordsum*x_coordsum); 
    cout<<"\nLinear Fit:\n"<<a<<"x+ "<<b<<endl;
}

int main(){
	int N;
	vector<Pt> intersections;
	vector<Line> lines;
	cout<<"Enter number of line segments:"<<endl;
	cin>>N;
	cout<<"P1X P1Y P2X P2Y"<<endl;
	for (int i = 0; i < N; ++i){
		double a,b,c,d;
		cin>>a;
		cin>>b;
		cin>>c;
		cin>>d;
		lines.push_back(Line(Pt(' ',a, b), Pt(' ',c,d)));
	}
	intersect(lines, intersections,false);
	int n=intersections.size();
	cout << "No. of intersection Pts:" << intersections.size()<< endl;
	double x_coord[n],y_coord[n];
	int i=0;
	for (auto it = intersections.begin(); it != intersections.end(); ++it)
	{
		x_coord[i]=it->x_coord;
		y_coord[i]=it->y_coord;
		cout <<"(" << it->x_coord << "," << it->y_coord << ") " << endl;
		i++;
	}
	cout<<endl;
	linearfitline(x_coord,y_coord,n);
	return 0;
}