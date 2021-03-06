#ifndef RTPINCOMINGSOURCE_H
#define RTPINCOMINGSOURCE_H

#include <map>

#include "config.h"
#include "rtp/RTPPacket.h"
#include "rtp/RTPSource.h"
#include "rtp/RTCPReport.h"
#include "WrapExtender.h"

struct RTPIncomingSource : public RTPSource
{
	DWORD	lostPackets;
	DWORD	dropPackets;
	DWORD	totalPacketsSinceLastSR;
	DWORD	totalBytesSinceLastSR;
	DWORD	minExtSeqNumSinceLastSR ;
	DWORD   lostPacketsSinceLastSR;
	QWORD   lastReceivedSenderNTPTimestamp;
	QWORD   lastReceivedSenderTime;
	QWORD   lastReceivedSenderReport;
	QWORD   lastReport;
	QWORD	lastPLI;
	DWORD   totalPLIs;
	DWORD	totalNACKs;
	QWORD	lastNACKed;
	DWORD	lastTimestamp;
	QWORD	lastTime;
	QWORD   firstReceivedSenderTime;
	QWORD   firstReceivedSenderTimestamp;
	int64_t skew;
	double  drift;
	WrapExtender timestampExtender;
	WrapExtender lastReceivedSenderRTPTimestampExtender;
	std::map<WORD,LayerSource> layers;
	
	RTPIncomingSource();
	virtual ~RTPIncomingSource() = default;
	
	WORD  ExtendSeqNum(WORD seqNum);
	WORD  RecoverSeqNum(WORD osn);
	
	DWORD ExtendTimestamp(DWORD timestamp);
	DWORD RecoverTimestamp(DWORD timestamp);
	
	void Update(QWORD now,DWORD seqNum,DWORD size,const LayerInfo &layerInfo);
	
	void Process(QWORD now, const RTCPSenderReport::shared& sr);
	
	
	virtual void Update(QWORD now,DWORD seqNum,DWORD size) override;
	virtual void Update(QWORD now) override;
	virtual void Reset() override;
	
	RTCPReport::shared CreateReport(QWORD now);
};

#endif /* RTPINCOMINGSOURCE_H */

