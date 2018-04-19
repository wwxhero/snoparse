#include "RoadNetParseBlock.h"

using namespace std;

CRoadNetParseBlock::CRoadNetParseBlock(void)
{
	SetBlockName("RoadNet");
}


CRoadNetParseBlock::~CRoadNetParseBlock(void)
{
}
CRoadNetParseBlock::EType CRoadNetParseBlock::GetType() const{

	CSnoValue val;
	if (GetField("Type", val))
		if (val.GetIntValue() == eROAD){
			return eROAD;
		}else{
			return eCORRIDOR;
		}
		
	else
		 return eROAD;
}
vector<CRoadNetParseBlock::TRoadNetPoint> CRoadNetParseBlock::GetRoadPoints() const{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<TRoadNetPoint> path;
	TRoadNetPoint point;
	if (GetField("RoadNetPath", vals)) {
		if (vals.size() % 5 != 0) {
			TCountError e("RoadNetPath", 5);
			throw e;
		}
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			point.x = (float)pVal->GetFloatValue();
			pVal++;
			point.y = (float)pVal->GetFloatValue();
			pVal++;
			point.z = (float)pVal->GetFloatValue();
			pVal++;
			point.w = (float)pVal->GetFloatValue();
			pVal++;
			point.att = (int)pVal->GetFloatValue();
			pVal++;
			point.ti = (float)pVal->GetFloatValue();
			pVal++;
			point.tj = (float)pVal->GetFloatValue();
			pVal++;
			point.tk = (float)pVal->GetFloatValue();
			path.push_back(point);
		}
	}
	return path;
}
vector< CRoadNetParseBlock::TRoadConnection > CRoadNetParseBlock::GetStartPathConnections()const{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<TRoadConnection> path;
	tuple<int,string, bool> point;
	int lane;
	string name;
	bool isStart;

	if (GetField("StartConnect", vals)) {
		if (vals.size() % 3 != 0) {
			TCountError e("StartConnect", 3);
			throw e;
		}
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			lane = pVal->GetIntValue();
			pVal++;
			name = pVal->GetStringValue();
			pVal++;
			isStart = pVal->GetIntValue() > 0;
			path.push_back(make_tuple(lane,name,isStart));
		}
	}
	return path;
}
vector< CRoadNetParseBlock::TRoadConnection > CRoadNetParseBlock::GetEndPathConnections()const{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<TRoadConnection> path;
	tuple<int,string, bool> point;
	int lane;
	string name;
	bool isStart;
	if (GetField("EndConnect", vals)) {
		if (vals.size() % 3 != 0) {
			TCountError e("EndConnect", 3);
			throw e;
		}
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			lane = pVal->GetIntValue();
			pVal++;
			name = pVal->GetStringValue();
			pVal++;
			isStart = pVal->GetIntValue() > 0;
			path.push_back(make_tuple(lane,name,isStart));
		}
	}
	return path;
}
string CRoadNetParseBlock::GetName(void) const{
	CSnoValue val;
	if (GetField("Name", val))
		return val.GetStringValue();
	else
		 return "";
}
string	CRoadNetParseBlock::GetIntersectionName() const{
	CSnoValue val;
	if (GetField("InterSectionName", val))
		return val.GetStringValue();
	else
		 return "";
}
void CRoadNetParseBlock::SetType(EType type){
	// Delete any "Name" fields
	ClearFields("Type");

	// Add new "Name" field.
	AddField("Type", type);
}
void CRoadNetParseBlock::SetLaneDirs(const vector<EDIR> &dirs){
	// Delete any "Traj" fields
	ClearFields("LaneDir");
	vector<EDIR>::const_iterator itr;
	// Add fields to the list
	for (itr = dirs.begin(); itr != dirs.end(); itr++) {
		AddField("LaneDir", *itr);
	}
}
void CRoadNetParseBlock::SetRoadPoints(const vector<TRoadNetPoint> &points){
	vector<TRoadNetPoint>::const_iterator itr;
	vector<double> trajsVec;

	// Delete any "Traj" fields
	ClearFields("RoadNetPath");

	// Add fields to the list
	for (itr = points.begin(); itr != points.end(); itr++) {
		trajsVec.clear();
		trajsVec.push_back(itr->x);
		trajsVec.push_back(itr->y);
		trajsVec.push_back(itr->z);
		trajsVec.push_back(itr->w);
		trajsVec.push_back(itr->att);
		trajsVec.push_back(itr->ti);
		trajsVec.push_back(itr->tj);
		trajsVec.push_back(itr->tk);
		AddField("RoadNetPath", trajsVec);
	}
}
void CRoadNetParseBlock::SetStartPathConnections(const vector< TRoadConnection > &connects){
	vector<tuple<int,string, bool>>::const_iterator itr;
	vector<tuple<int,string, bool>> trajsVec;

	// Delete any "Traj" fields
	ClearFields("StartConnect");

	// Add fields to the list
	for (itr = connects.begin(); itr != connects.end(); itr++) {
		AddField("StartConnect", tr1::get<0>(*itr));
		AddField("StartConnect", tr1::get<1>(*itr));
		AddField("StartConnect", tr1::get<2>(*itr));
	}

}
void CRoadNetParseBlock::SetEndPathConnections(const vector< TRoadConnection > &connects){
	vector<tuple<int,string, bool>>::const_iterator itr;
	vector<tuple<int,string, bool>> trajsVec;

	// Delete any "Traj" fields
	ClearFields("EndConnect");

	// Add fields to the list
	for (itr = connects.begin(); itr != connects.end(); itr++) {
		AddField("EndConnect", tr1::get<0>(*itr));
		AddField("EndConnect", tr1::get<1>(*itr));
		AddField("EndConnect", tr1::get<2>(*itr));
	}
}
void CRoadNetParseBlock::SetName(const string &name){
	// Delete any "Name" fields
	ClearFields("Name");

	// Add new "Name" field.
	AddField("Name", name);
}

void CRoadNetParseBlock::SetIntersectionName(const string &name){
	CSnoValue val;
	// Delete any "Name" fields
	ClearFields("InterSectionName");
	// Add new "Name" field.
	AddField("InterSectionName", name);
}