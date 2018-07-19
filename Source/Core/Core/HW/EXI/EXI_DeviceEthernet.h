// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <atomic>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "Common/Flag.h"
#include "Core/HW/EXI/EXI_Device.h"

class PointerWrap;

namespace ExpansionInterface
{
// Network Control Register A
enum NCRA
{
  NCRA_RESET = 0x01,  // RESET
  NCRA_ST0 = 0x02,    // Start transmit command/status
  NCRA_ST1 = 0x04,    // "
  NCRA_SR = 0x08      // Start Receive
};

// Network Control Register B
enum NCRB
{
  NCRB_PR = 0x01,     // Promiscuous Mode
  NCRB_CA = 0x02,     // Capture Effect Mode
  NCRB_PM = 0x04,     // Pass Multicast
  NCRB_PB = 0x08,     // Pass Bad Frame
  NCRB_AB = 0x10,     // Accept Broadcast
  NCRB_HBD = 0x20,    // reserved
  NCRB_RXINTC = 0xC0  // Receive Interrupt Counter (mask)
};

// Interrupt Mask Register
// Interrupt Register
enum Interrupts
{
  INT_FRAG = 0x01,      // Fragment Counter
  INT_R = 0x02,         // Receive
  INT_T = 0x04,         // Transmit
  INT_R_ERR = 0x08,     // Receive Error
  INT_T_ERR = 0x10,     // Transmit Error
  INT_FIFO_ERR = 0x20,  // FIFO Error
  INT_BUS_ERR = 0x40,   // BUS Error
  INT_RBF = 0x80        // RX Buffer Full
};

// NWAY Configuration Register
enum NWAYC
{
  NWAYC_FD = 0x01,        // Full Duplex Mode
  NWAYC_PS100_10 = 0x02,  // Port Select 100/10
  NWAYC_ANE = 0x04,       // Autonegotiate enable

  // Autonegotiation status bits...

  NWAYC_NTTEST = 0x40,  // Reserved
  NWAYC_LTE = 0x80      // Link Test Enable
};

enum NWAYS
{
  NWAYS_LS10 = 0x01,
  NWAYS_LS100 = 0x02,
  NWAYS_LPNWAY = 0x04,
  NWAYS_ANCLPT = 0x08,
  NWAYS_100TXF = 0x10,
  NWAYS_100TXH = 0x20,
  NWAYS_10TXF = 0x40,
  NWAYS_10TXH = 0x80
};

enum MISC1
{
  MISC1_BURSTDMA = 0x01,
  MISC1_DISLDMA = 0x02,
  MISC1_TPF = 0x04,
  MISC1_TPH = 0x08,
  MISC1_TXF = 0x10,
  MISC1_TXH = 0x20,
  MISC1_TXFIFORST = 0x40,
  MISC1_RXFIFORST = 0x80
};

enum MISC2
{
  MISC2_HBRLEN0 = 0x01,
  MISC2_HBRLEN1 = 0x02,
  MISC2_RUNTSIZE = 0x04,
  MISC2_DREQBCTRL = 0x08,
  MISC2_RINTSEL = 0x10,
  MISC2_ITPSEL = 0x20,
  MISC2_A11A8EN = 0x40,
  MISC2_AUTORCVR = 0x80
};

enum
{
  BBA_NCRA = 0x00,
  BBA_NCRB = 0x01,

  BBA_LTPS = 0x04,
  BBA_LRPS = 0x05,

  BBA_IMR = 0x08,
  BBA_IR = 0x09,

  BBA_BP = 0x0a,
  BBA_TLBP = 0x0c,
  BBA_TWP = 0x0e,
  BBA_IOB = 0x10,
  BBA_TRP = 0x12,
  BBA_RWP = 0x16,
  BBA_RRP = 0x18,
  BBA_RHBP = 0x1a,

  BBA_RXINTT = 0x14,

  BBA_NAFR_PAR0 = 0x20,
  BBA_NAFR_PAR1 = 0x21,
  BBA_NAFR_PAR2 = 0x22,
  BBA_NAFR_PAR3 = 0x23,
  BBA_NAFR_PAR4 = 0x24,
  BBA_NAFR_PAR5 = 0x25,
  BBA_NAFR_MAR0 = 0x26,
  BBA_NAFR_MAR1 = 0x27,
  BBA_NAFR_MAR2 = 0x28,
  BBA_NAFR_MAR3 = 0x29,
  BBA_NAFR_MAR4 = 0x2a,
  BBA_NAFR_MAR5 = 0x2b,
  BBA_NAFR_MAR6 = 0x2c,
  BBA_NAFR_MAR7 = 0x2d,

  BBA_NWAYC = 0x30,
  BBA_NWAYS = 0x31,

  BBA_GCA = 0x32,

  BBA_MISC = 0x3d,

  BBA_TXFIFOCNT = 0x3e,
  BBA_WRTXFIFOD = 0x48,

  BBA_MISC2 = 0x50,

  BBA_SI_ACTRL = 0x5c,
  BBA_SI_STATUS = 0x5d,
  BBA_SI_ACTRL2 = 0x60
};

enum
{
  BBA_NUM_PAGES = 0x10,
  BBA_PAGE_SIZE = 0x100,
  BBA_MEM_SIZE = BBA_NUM_PAGES * BBA_PAGE_SIZE,
  BBA_TXFIFO_SIZE = 1518
};

enum
{
  EXI_DEVTYPE_ETHER = 0x04020200
};

enum SendStatus
{
  DESC_CC0 = 0x01,
  DESC_CC1 = 0x02,
  DESC_CC2 = 0x04,
  DESC_CC3 = 0x08,
  DESC_CRSLOST = 0x10,
  DESC_UF = 0x20,
  DESC_OWC = 0x40,
  DESC_OWN = 0x80
};

enum RecvStatus
{
  DESC_BF = 0x01,
  DESC_CRC = 0x02,
  DESC_FAE = 0x04,
  DESC_FO = 0x08,
  DESC_RW = 0x10,
  DESC_MF = 0x20,
  DESC_RF = 0x40,
  DESC_RERR = 0x80
};

#define BBA_RECV_SIZE 0x800

class CEXIETHERNET : public IEXIDevice
{
public:
  CEXIETHERNET();
  virtual ~CEXIETHERNET();
  void SetCS(int cs) override;
  bool IsPresent() const override;
  bool IsInterruptSet() override;
  void ImmWrite(u32 data, u32 size) override;
  u32 ImmRead(u32 size) override;
  void DMAWrite(u32 addr, u32 size) override;
  void DMARead(u32 addr, u32 size) override;
  void DoState(PointerWrap& p) override;

private:
  struct
  {
    enum
    {
      READ,
      WRITE
    } direction;

    enum
    {
      EXI,
      MX
    } region;

    u16 address;
    bool valid;
  } transfer = {};

  enum
  {
    EXI_ID,
    REVISION_ID,
    INTERRUPT_MASK,
    INTERRUPT,
    DEVICE_ID,
    ACSTART,
    HASH_READ = 8,
    HASH_WRITE,
    HASH_STATUS = 0xb,
    RESET = 0xf
  };

  // exi regs
  struct EXIStatus
  {
    enum
    {
      TRANSFER = 0x80
    };

    u8 revision_id = 0;  // 0xf0
    u8 interrupt_mask = 0;
    u8 interrupt = 0;
    u16 device_id = 0xD107;
    u8 acstart = 0x4E;
    u32 hash_challenge = 0;
    u32 hash_response = 0;
    u8 hash_status = 0;
  } exi_status;

  struct Descriptor
  {
    u32 word;

    inline void set(u32 const next_page, u32 const packet_length, u32 const status)
    {
      word = 0;
      word |= (status & 0xff) << 24;
      word |= (packet_length & 0xfff) << 12;
      word |= next_page & 0xfff;
    }
  };

  inline u16 page_ptr(int const index) const
  {
    return ((u16)mBbaMem[index + 1] << 8) | mBbaMem[index];
  }

  inline u8* ptr_from_page_ptr(int const index) const { return &mBbaMem[page_ptr(index) << 8]; }
  bool IsMXCommand(u32 const data);
  bool IsWriteCommand(u32 const data);
  const char* GetRegisterName() const;
  void MXHardReset();
  void MXCommandHandler(u32 data, u32 size);
  void DirectFIFOWrite(const u8* data, u32 size);
  void SendFromDirectFIFO();
  void SendFromPacketBuffer();
  void SendComplete();
  u8 HashIndex(const u8* dest_eth_addr);
  bool RecvMACFilter();
  void inc_rwp();
  bool RecvHandlePacket();

  std::unique_ptr<u8[]> mBbaMem;
  std::unique_ptr<u8[]> tx_fifo;

  // TAP interface
  static void ReadThreadHandler(CEXIETHERNET* self);
  bool Activate();
  void Deactivate();
  bool IsActivated();
  bool SendFrame(const u8* frame, u32 size);
  bool RecvInit();
  void RecvStart();
  void RecvStop();

  std::unique_ptr<u8[]> mRecvBuffer;
  u32 mRecvBufferLength = 0;

#if defined(_WIN32)
  HANDLE mHAdapter = INVALID_HANDLE_VALUE;
  OVERLAPPED mReadOverlapped = {};
  OVERLAPPED mWriteOverlapped = {};
  std::vector<u8> mWriteBuffer;
  bool mWritePending = false;
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__)
  int fd = -1;
#endif

#if defined(_WIN32) || defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) ||          \
    defined(__OpenBSD__)
  std::thread readThread;
  Common::Flag readEnabled;
  Common::Flag readThreadShutdown;
#endif
};
}  // namespace ExpansionInterface
