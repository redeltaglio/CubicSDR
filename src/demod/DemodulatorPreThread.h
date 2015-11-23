#pragma once

#include <queue>
#include <vector>

#include "CubicSDRDefs.h"
#include "DemodDefs.h"
#include "DemodulatorWorkerThread.h"

class DemodulatorInstance;

class DemodulatorPreThread : public IOThread {
public:

    DemodulatorPreThread(DemodulatorInstance *parent);
    ~DemodulatorPreThread();

    void run();
    
    void setDemodType(std::string demodType);
    std::string getDemodType();

    void setFrequency(long long sampleRate);
    long long getFrequency();

    void setSampleRate(long long sampleRate);
    long long getSampleRate();
    
    void setBandwidth(int bandwidth);
    int getBandwidth();
    
    void setAudioSampleRate(int rate);
    int getAudioSampleRate();
    
    void initialize();
    void terminate();

    Modem *getModem();
    ModemKit *getModemKit();
    
protected:
    DemodulatorInstance *parent;
    msresamp_crcf iqResampler;
    double iqResampleRatio;
    std::vector<liquid_float_complex> resampledData;

    Modem *cModem;
    ModemKit *cModemKit;
    
    long long currentSampleRate, newSampleRate;
    long long currentFrequency, newFrequency;
    int currentBandwidth, newBandwidth;
    int currentAudioSampleRate, newAudioSampleRate;

    std::atomic_bool sampleRateChanged, frequencyChanged, bandwidthChanged, audioSampleRateChanged;
    
    nco_crcf freqShifter;
    int shiftFrequency;

    std::atomic_bool initialized;
    std::atomic_bool demodTypeChanged;
    std::string demodType;
    std::string newDemodType;

    DemodulatorWorkerThread *workerThread;
    std::thread *t_Worker;

    DemodulatorThreadWorkerCommandQueue *workerQueue;
    DemodulatorThreadWorkerResultQueue *workerResults;

    DemodulatorThreadInputQueue* iqInputQueue;
    DemodulatorThreadPostInputQueue* iqOutputQueue;
    DemodulatorThreadCommandQueue* threadQueueNotify;
};
