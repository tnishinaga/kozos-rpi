#include "defines.h"
#include "spi.h"

typedef enum {
    RCR = 0,
    RBM = 1,
    WCR = 2,
    WBM = 3,
    BFS = 4,
    BFC = 5,
    SC  = 7,
} ENC28J60_OPCODE;

#define ENC28J60_PARAM_RBM  0b11010
#define ENC28J60_PARAM_WBM  ENC28J60_PARAM_RBM
#define ENC28J60_PARAM_SC   0b11111


uint8 enc28j60_spi_cs = 0;
uint8 enc28j60_spi_mode = 0;

int enc28j60_spi_setup(uint8 cs, uint8 mode, uint16 clock_div)
{
    // set slowest clock(to debug easyly)
    spi_clock_div(clock_div);
    
    if (bad_cs_range(cs)) {
        return -1;
    }
    if (bad_mode_range(mode)) {
        return -1;
    }
    enc28j60_spi_cs = cs;
    enc28j60_spi_mode = mode;
    return 0;
}

static inline uint8 enc28j60_cmd(ENC28J60_OPCODE op, uint8 args)
{
    return (op << 5) | args;
}


int enc28j60_software_reset(void)
{
    spi_start(enc28j60_spi_cs, enc28j60_spi_mode);
    spi_write(enc28j60_cmd(SC, 0b11111));
    spi_end();
    return 0;
}

#define ENC28J60_BANK_EIE      0x1B
#define ENC28J60_BANK_EIR      0x1C
#define ENC28J60_BANK_ESTAT    0x1D
#define ENC28J60_BANK_ECON2    0x1E
#define ENC28J60_BANK_ECON1    0x1F

#define ENC28J60_BANK0_ETXSTL   0x04
#define ENC28J60_BANK0_ETXSTH   0x05
#define ENC28J60_BANK0_ETXNDL   0x06
#define ENC28J60_BANK0_ETXNDH   0x07
#define ENC28J60_BANK0_ERXSTL   0x08
#define ENC28J60_BANK0_ERXSTH   0x09
#define ENC28J60_BANK0_ERXNDL   0x0A
#define ENC28J60_BANK0_ERXNDH   0x0B
#define ENC28J60_BANK0_ERXRDPTL 0x0C
#define ENC28J60_BANK0_ERXRDPTH 0x0D
#define ENC28J60_BANK0_ERXWRPTL 0x0E
#define ENC28J60_BANK0_ERXWRPTH 0x0F

#define ENC28J60_BANK1_ERXFCON  0x18

#define ENC28J60_BANK2_MACON1   0x00
#define ENC28J60_BANK2_MACON3   0x02
#define ENC28J60_BANK2_MACON4   0x03
#define ENC28J60_BANK2_MAMXFLL  0x0A
#define ENC28J60_BANK2_MAMXFLH  0x0B
#define ENC28J60_BANK2_MABBIPG  0x04
#define ENC28J60_BANK2_MAIPGLL  0x06
#define ENC28J60_BANK2_MAIPGLH  0x07

#define ENC28J60_BANK3_MAADR5   0x00
#define ENC28J60_BANK3_MAADR6   0x01
#define ENC28J60_BANK3_MAADR3   0x02
#define ENC28J60_BANK3_MAADR4   0x03
#define ENC28J60_BANK3_MAADR1   0x04
#define ENC28J60_BANK3_MAADR2   0x05



#define ENC28J60_ESTAT_INT      (1 << 7)
#define ENC28J60_ESTAT_BUFFER   (1 << 6)
#define ENC28J60_ESTAT_LATECOL  (1 << 4)
#define ENC28J60_ESTAT_RXBUSY   (1 << 2)
#define ENC28J60_ESTAT_TXABT    (1 << 1)
#define ENC28J60_ESTAT_CLKRDY   (1 << 0)

#define ENC28J60_ECON1_TXRST    (1 << 7)
#define ENC28J60_ECON1_RXRST    (1 << 6)
#define ENC28J60_ECON1_DMAST    (1 << 5)
#define ENC28J60_ECON1_CSUMEN   (1 << 4)
#define ENC28J60_ECON1_TXRTS    (1 << 3)
#define ENC28J60_ECON1_RXEN     (1 << 2)
#define ENC28J60_ECON1_BSEL1    (1 << 1)
#define ENC28J60_ECON1_BSEL0    (1 << 0)

#define ENC28J60_ECON2_AUTOINC  (1 << 7)
#define ENC28J60_ECON2_PKTDEC   (1 << 6)
#define ENC28J60_ECON2_PWRSV    (1 << 5)
#define ENC28J60_ECON2_VRPS     (1 << 3)

#define ENC28J60_EIE_INTIE      (1 << 7)
#define ENC28J60_EIE_PKTIE      (1 << 6)
#define ENC28J60_EIE_DMAIE      (1 << 5)
#define ENC28J60_EIE_LINKIE     (1 << 4)
#define ENC28J60_EIE_TXIE       (1 << 3)
#define ENC28J60_EIE_TXERIE     (1 << 1)
#define ENC28J60_EIE_RXERIE     (1 << 0)

#define ENC28J60_EIR_PKTIF      (1 << 6)
#define ENC28J60_EIR_DMAIF      (1 << 5)
#define ENC28J60_EIR_LINKIF     (1 << 4)
#define ENC28J60_EIR_TXIF       (1 << 3)
#define ENC28J60_EIR_TXERIF     (1 << 1)
#define ENC28J60_EIR_EXERIF     (1 << 0)


#define ENC28J60_ERXFCON_UCEN   (1 << 7)
#define ENC28J60_ERXFCON_ANDOR  (1 << 6)
#define ENC28J60_ERXFCON_CRCEN  (1 << 5)
#define ENC28J60_ERXFCON_PMEN   (1 << 4)
#define ENC28J60_ERXFCON_MPEN   (1 << 3)
#define ENC28J60_ERXFCON_HTEN   (1 << 2)
#define ENC28J60_ERXFCON_MCEN   (1 << 1)
#define ENC28J60_ERXFCON_BCEN   (1 << 0)

#define ENC28J60_MACON1_TXPAUS  (1 << 3)
#define ENC28J60_MACON1_RXPAUS  (1 << 2)
#define ENC28J60_MACON1_PASSALL (1 << 1)
#define ENC28J60_MACON1_MARXEN  (1 << 0)

#define ENC28J60_MACON3_PADCFG2 (1 << 7)
#define ENC28J60_MACON3_PADCFG1 (1 << 6)
#define ENC28J60_MACON3_PADCFG0 (1 << 5)
#define ENC28J60_MACON3_PADCFG(x) (x << 5)
#define ENC28J60_MACON3_TXCRCEN (1 << 4)
#define ENC28J60_MACON3_PHDREN  (1 << 3)
#define ENC28J60_MACON3_HFRMEN  (1 << 2)
#define ENC28J60_MACON3_FRMLNEN (1 << 1)
#define ENC28J60_MACON3_FULDPX  (1 << 0)



int enc28j60_register_read_1byte(uint8 addr)
{
    spi_start(enc28j60_spi_cs, enc28j60_spi_mode);
    spi_write(enc28j60_cmd(RCR, addr));
    int result = spi_write(0);
    spi_end();
    return result;
}

int enc28j60_register_write_1byte(uint8 addr, uint8 data)
{
    spi_start(enc28j60_spi_cs, enc28j60_spi_mode);
    spi_write(enc28j60_cmd(WCR, addr));
    spi_write(data);
    spi_end();
    return 0;
}

static inline void enc28j60_select_bank(uint8 bank)
{
    uint32 econ1 = enc28j60_register_read_1byte(ENC28J60_BANK_ECON1);
    econ1 &= ~(ENC28J60_ECON1_BSEL1 | ENC28J60_ECON1_BSEL0);
    econ1 |= bank;
    enc28j60_register_write_1byte(ENC28J60_BANK_ECON1, bank);
}

static inline void enc28j60_set_rxbuffer_range(uint16 addr_start, uint16 addr_end)
{
    // change register bank 0
    enc28j60_select_bank(0);
    // set rx buffer start address
    enc28j60_register_write_1byte(ENC28J60_BANK0_ERXSTL, addr_start & 0xff);
    enc28j60_register_write_1byte(ENC28J60_BANK0_ERXSTH, addr_start >> 8);
    // set rx buffer end address
    enc28j60_register_write_1byte(ENC28J60_BANK0_ERXNDL, addr_end & 0xff);
    enc28j60_register_write_1byte(ENC28J60_BANK0_ERXNDH, addr_end >> 8);
    // set rx buffer read pointer
    enc28j60_register_write_1byte(ENC28J60_BANK0_ERXRDPTL, addr_start & 0xff);
    enc28j60_register_write_1byte(ENC28J60_BANK0_ERXRDPTH, addr_start >> 8);
}

int enc28j60_init(void)
{
    // reset
    enc28j60_software_reset();
    // wait until reset done
    // Rev. B4 Silicon Errata point より、 CLKRDY は動かないのでeasy_wait
    // while(!(enc28j60_register_read_1byte(ENC28J60_BANK_ESTAT) & ENC28J60_ESTAT_CLKRDY));
    for (volatile int i = 0; i < 100000; i++);

    // init buffer size
    enc28j60_set_rxbuffer_range(0x1000, 0x1FFF);
    // set rx filter off
    enc28j60_select_bank(1);
    enc28j60_register_write_1byte(ENC28J60_BANK1_ERXFCON, 
        // ENC28J60_ERXFCON_UCEN |
        // ENC28J60_ERXFCON_ANDOR |
        // ENC28J60_ERXFCON_CRCEN |
        // ENC28J60_ERXFCON_PMEN |
        // ENC28J60_ERXFCON_MPEN |
        // ENC28J60_ERXFCON_HTEN |
        // ENC28J60_ERXFCON_MCEN |
        // ENC28J60_ERXFCON_BCEN |
        0
    );
    // wait until setup done
    while(!(enc28j60_register_read_1byte(ENC28J60_BANK_ESTAT) & ENC28J60_ESTAT_CLKRDY));
    
    // setup MAC address
    enc28j60_select_bank(2);
    enc28j60_register_write_1byte(ENC28J60_BANK2_MACON1, 
        ENC28J60_MACON1_MARXEN |
        ENC28J60_MACON1_TXPAUS |
        ENC28J60_MACON1_RXPAUS |
        0
    );
    enc28j60_register_write_1byte(ENC28J60_BANK2_MACON3, 
        ENC28J60_MACON3_PADCFG(0b111) |
        ENC28J60_MACON3_TXCRCEN |
        ENC28J60_MACON3_FRMLNEN |
        ENC28J60_MACON3_FULDPX |
        0
    );
    // set max flame length
    enc28j60_register_write_1byte(ENC28J60_BANK2_MAMXFLL, (uint8)1518 & 0xff);
    enc28j60_register_write_1byte(ENC28J60_BANK2_MAMXFLH, (uint8)1518 >> 8);
    // set MABBIPG to full-duplex(15)
    enc28j60_register_write_1byte(ENC28J60_BANK2_MABBIPG, 0x15);
    enc28j60_register_write_1byte(ENC28J60_BANK2_MAIPGLL, 0x12);
    enc28j60_register_write_1byte(ENC28J60_BANK2_MAIPGLH, 0);
    // set MAC address
    // DE:AD:BE:AF:01:02
    enc28j60_select_bank(3);
    enc28j60_register_write_1byte(ENC28J60_BANK3_MAADR1, 0x01);
    enc28j60_register_write_1byte(ENC28J60_BANK3_MAADR2, 0x01);
    enc28j60_register_write_1byte(ENC28J60_BANK3_MAADR3, 0x01);
    enc28j60_register_write_1byte(ENC28J60_BANK3_MAADR4, 0x01);
    enc28j60_register_write_1byte(ENC28J60_BANK3_MAADR5, 0x01);
    enc28j60_register_write_1byte(ENC28J60_BANK3_MAADR6, 0x01);

    // TODO: PHYレジスタを設定する
    // MIREGADRレジスタにアクセスしたいPHYレジスタのアドレスを入れる
    // MIWRLに書きたいデータの下位8bitを書き込む
    // MIWRHに書きたいデータの上位8bitを書きこむ
    // 1msまつ

    // set AUTOINC flag
    enc28j60_register_write_1byte(ENC28J60_BANK_ECON2, ENC28J60_ECON2_AUTOINC);

    return 0;
}

// void enc28j60_register_mask_clr(uint8 bank, uint8 addr, uint8 mask)
// {

// }

// void enc28j60_register_mask_set(uint8 bank, uint8 addr, uint8 mask)
// {
    
// }


int enc28j60_send_packet(uint8 *data, uint32 len)
{
    // TODO: ICのエラッタを調べる

    // ETXST でバッファの開始アドレスを設定する
    enc28j60_register_write_1byte(ENC28J60_BANK0_ETXSTL, 0);
    enc28j60_register_write_1byte(ENC28J60_BANK0_ETXSTH, 0);
    // WBMコマンドでデータを書き込む
    spi_start(enc28j60_spi_cs, enc28j60_spi_mode);
    spi_write(enc28j60_cmd(WBM, ENC28J60_PARAM_WBM));
    spi_write(0x0E);    // control byte
    for (uint32 i = 0; i < len; i++) {
        spi_write(data[i]);
    }
    spi_end();

    // ETXND で書き込んだデータの最後のアドレスを設定する
    enc28j60_register_write_1byte(ENC28J60_BANK0_ETXNDL, len & 0xff);
    enc28j60_register_write_1byte(ENC28J60_BANK0_ETXNDH, len >> 8);
    // EIR.TXIFをクリアし、EIE.TXIEをセットする
    uint32 eir = enc28j60_register_read_1byte(ENC28J60_BANK_EIR);
    eir &= ~((uint32)ENC28J60_EIR_TXIF);
    enc28j60_register_write_1byte(ENC28J60_BANK_EIR, eir);
    uint32 eie = enc28j60_register_read_1byte(ENC28J60_BANK_EIE);
    eir |= ENC28J60_EIE_TXIE;
    enc28j60_register_write_1byte(ENC28J60_BANK_EIE, eie);
    // ECON1.TXRTSをセットして送信を開始する
    uint32 econ1 = enc28j60_register_read_1byte(ENC28J60_BANK_ECON1);
    econ1 |= ENC28J60_ECON1_TXRTS;
    enc28j60_register_write_1byte(ENC28J60_BANK_ECON1, econ1);
    return len;
}