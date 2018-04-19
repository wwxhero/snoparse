#pragma once
#include "hcsmspec.h"
#include <tuple>
class CRoadNetParseBlock :
	public CSnoBlock
{
public:
	CRoadNetParseBlock(void);
	~CRoadNetParseBlock(void);
	enum EType{
		eROAD =1,
		eCORRIDOR = 2
	};
	enum EDIR{
		eNONE = 0,
		ePOSITIVE = 1,
		eNEGITIVE = 2
	};
	enum ETupple{
		eATSTARTCORR =0,
		eNAME        =1,
		eATSTARTROAD= 2,
	}; //< element ordering for TRoadConnection
	struct TRoadNetPoint{
		float x;
		float y;
		float z;
		float w;
		float ti; //tangent vector
		float tj;
		float tk;
		int att;
	};
	typedef std::tuple<int,std::string,bool> TRoadConnection; //<lane, name of target corridor, is Start?
	EType GetType() const;
	std::vector<TRoadNetPoint>      GetRoadPoints() const;
	std::vector< TRoadConnection > GetStartPathConnections() const;
	std::vector< TRoadConnection > GetEndPathConnections() const;
	std::string			           GetName(void) const;
	std::string					   GetIntersectionName() const;

	void SetLaneDirs(const std::vector<EDIR> &dirs);
	void SetType(EType);
	void SetRoadPoints(const std::vector<TRoadNetPoint> &points);
	void SetStartPathConnections(const std::vector<TRoadConnection> &connects);
	void SetEndPathConnections(const std::vector< TRoadConnection > &connects);
	void SetName(const std::string &name);
	void SetIntersectionName(const std::string &name);
	void GetLaneDirs(const std::vector<EDIR> &dirs);

};

