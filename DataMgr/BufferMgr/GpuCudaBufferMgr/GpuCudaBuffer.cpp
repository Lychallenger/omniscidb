#include "GpuCudaBuffer.h"
#include "../../../CudaMgr/CudaMgr.h"

namespace Buffer_Namespace {

    GpuCudaBuffer::GpuCudaBuffer(BufferMgr *bm, BufferList::iterator segIt, const int deviceId, CudaMgr_Namespace::CudaMgr *cudaMgr,const size_t pageSize, const size_t numBytes): Buffer(bm, segIt, deviceId, pageSize, numBytes), cudaMgr_(cudaMgr) {} 

    void GpuCudaBuffer::readData(int8_t * const dst, const size_t numBytes, const MemoryLevel dstBufferType, const size_t offset) {
        if (dstBufferType == CPU_LEVEL) {
            cudaMgr_->copyDeviceToHost(dst,mem_+offset,numBytes,deviceId_); // need to replace 0 with gpu num 
        }
        else if (dstBufferType == GPU_LEVEL) {
            //@todo fill this in
            //CudaUtils::copyGpuToGpu(dst, mem_ + offset, numBytes, 1, dst->getDeviceId());
            //@todo, populate device id
            //CudaUtils::copyGpuToGpu(dst, mem_ + offset, numBytes, 1, 0);
            cudaMgr_->copyDeviceToDevice(dst,mem_+offset,numBytes,deviceId_,deviceId_);

        }
        else {
            throw std::runtime_error("Unsupported buffer type");
        }
    }

    void GpuCudaBuffer::writeData(int8_t * const src, const size_t numBytes, const MemoryLevel srcBufferType, const size_t offset) {
        if (srcBufferType == CPU_LEVEL) {
            cudaMgr_->copyHostToDevice(mem_+offset,src,numBytes,deviceId_); // need to replace 0 with gpu num 

        }
        else if (srcBufferType == GPU_LEVEL) {
            cudaMgr_->copyDeviceToDevice(mem_+offset,src,numBytes,deviceId_,deviceId_);
            //CudaUtils::copyGpuToGpu(mem_ + offset, src, numBytes, 1, deviceId_);
            //@todo fill this in
        }
        else {
            throw std::runtime_error("Unsupported buffer type");
        }
    }

} // Buffer_Namespace
