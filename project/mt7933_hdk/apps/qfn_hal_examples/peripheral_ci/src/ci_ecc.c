#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ci.h"
#include "ci_cli.h"
#include "hal.h"
#include "hal_ecc.h"

#define ECC_SRAM_SIZE_DWORD      17

typedef struct _ts_ecc_ecdsa_golden {
    uint32_t num;
    uint32_t e[ECC_SRAM_SIZE_DWORD];
    uint32_t d[ECC_SRAM_SIZE_DWORD];
    uint32_t k[ECC_SRAM_SIZE_DWORD];
    uint32_t r[ECC_SRAM_SIZE_DWORD];
    uint32_t s[ECC_SRAM_SIZE_DWORD];
    uint32_t Qx[ECC_SRAM_SIZE_DWORD];
    uint32_t Qy[ECC_SRAM_SIZE_DWORD];
    uint32_t dQx[ECC_SRAM_SIZE_DWORD];
    uint32_t dQy[ECC_SRAM_SIZE_DWORD];
} ts_ecc_ecdsa_golden;

/*
e:  | ECC9E5C91394232EAD42EE7AD0235282F7A1F793A348477D
d:  | 967324301110B7A598173C3C5C24F9BD1AE2D6B0924312A8
k:  | 2A5FBBB05B06D928BEE0E3E20BBB3A6FCEE41724B1ACDCEE
r:  | F627B3736BA469AAC7F53FF79C00C61C910DEF3DBFF1DCF7
s:  | C1436820B771C77773C986CD39B5ED08B691993B45E97A33
Qx: | 1E213D30F4094A9F467A2E3E882782614B202B2F14AD02E3
Qy: | 47ADC5DA2100DECAEF6171C85B39DB24BD09F1AD7E636499
dQx:| 004193DA5697B169CE1BC0301C24F23610E69F0E7B9096C1
dQy:| C73DE7B90F7F127C19ACC03BE19FC13C3AD7437185013C5E
*/
static ts_ecc_ecdsa_golden st_ecdsa_golden_192 = {
    1,
    {
        0xA348477D, 0xF7A1F793, 0xD0235282, 0xAD42EE7A, 0x1394232E, 0xECC9E5C9,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x924312A8, 0x1AE2D6B0, 0x5C24F9BD, 0x98173C3C, 0x1110B7A5, 0x96732430,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xB1ACDCEE, 0xCEE41724, 0x0BBB3A6F, 0xBEE0E3E2, 0x5B06D928, 0x2A5FBBB0,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xBFF1DCF7, 0x910DEF3D, 0x9C00C61C, 0xC7F53FF7, 0x6BA469AA, 0xF627B373,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x45E97A33, 0xB691993B, 0x39B5ED08, 0x73C986CD, 0xB771C777, 0xC1436820,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x14AD02E3, 0x4B202B2F, 0x88278261, 0x467A2E3E, 0xF4094A9F, 0x1E213D30,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x7E636499, 0xBD09F1AD, 0x5B39DB24, 0xEF6171C8, 0x2100DECA, 0x47ADC5DA,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x7B9096C1, 0x10E69F0E, 0x1C24F236, 0xCE1BC030, 0x5697B169, 0x004193DA,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x85013C5E, 0x3AD74371, 0xE19FC13C, 0x19ACC03B, 0x0F7F127C, 0xC73DE7B9,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
};

/*
e:  | DE17EFDB9B5E55522F2F9CE8DAF3322D02F58F19E48CBA178F56A6C8
d:  | DF8A579C0C8250294096A03DC345EFBF7C2FE4301A37D9CC33C13595
k:  | 75F26DDD93CC92C75D4073599BA0DBF408D536AF9D4C8169EE2A6C93
r:  | ED300C054BFDCCC1462A79A69296A04E64B3EF6F250DED92D77BCC07
s:  | A8A6B1B28C9255CD736B828105FF42A9EA4C9EF004F6E03FB3CB9871
Qx: | E75E9BA7DCE0A562B18AAC5C4677845A5EEF5A3A95F066BA6D250DB3
Qy: | A8E538E616CF90893DFF81FA3DF3B22254F373353D6064A7D616C127
dQx:| F2523D5E323B7FF376A46B012E1F89CBCE6391FCEFBD782416D330BF
dQy:| 6FC1658D17C485A74C81841881C0C5F8C4F9644DBB655630891AC887
*/
static ts_ecc_ecdsa_golden st_ecdsa_golden_224 = {
    1,
    {
        0x8F56A6C8, 0xE48CBA17, 0x02F58F19, 0xDAF3322D, 0x2F2F9CE8, 0x9B5E5552,
        0xDE17EFDB, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x33C13595, 0x1A37D9CC, 0x7C2FE430, 0xC345EFBF, 0x4096A03D, 0x0C825029,
        0xDF8A579C, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xEE2A6C93, 0x9D4C8169, 0x08D536AF, 0x9BA0DBF4, 0x5D407359, 0x93CC92C7,
        0x75F26DDD, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xD77BCC07, 0x250DED92, 0x64B3EF6F, 0x9296A04E, 0x462A79A6, 0x4BFDCCC1,
        0xED300C05, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xB3CB9871, 0x04F6E03F, 0xEA4C9EF0, 0x05FF42A9, 0x736B8281, 0x8C9255CD,
        0xA8A6B1B2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x6D250DB3, 0x95F066BA, 0x5EEF5A3A, 0x4677845A, 0xB18AAC5C, 0xDCE0A562,
        0xE75E9BA7, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xD616C127, 0x3D6064A7, 0x54F37335, 0x3DF3B222, 0x3DFF81FA, 0x16CF9089,
        0xA8E538E6, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x16D330BF, 0xEFBD7824, 0xCE6391FC, 0x2E1F89CB, 0x76A46B01, 0x323B7FF3,
        0xF2523D5E, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x891AC887, 0xBB655630, 0xC4F9644D, 0x81C0C5F8, 0x4C818418, 0x17C485A7,
        0x6FC1658D, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
};

/*
e:  | 1FDA215619F5BF25637536F7C535C273C64E5D615F3CDF14266815920377BCC0
d:  | ACEC122D3B51E0FC84335DD3F013D5637C7A99474DC4192FFDAF4EE1A112ED54
k:  | C8BDD79F1958A4282DEA70548566A7E8A3CE7B213694C98E0AEBFE6DFD11A53D
r:  | 2F350F06B21737AED33E3511253EB72ABD362686FDAB95A98926F457F345B5B5
s:  | 338AE2FA151E00C00749A6B2CED6F8A5A686FD6E135D7EF3814492C35313B579
Qx: | 5AF2E9D1E75F70CD65455B8E6AE6900EAAAA74F1684E285C8F335540C3E79B79
Qy: | EC52712FD8565D9D32F97CCB9A296177C5EC1D8BB69BA98B50FDF6D93016AC86
dQx:| B40B89A5FF7C546D4C23B820A6155C5834901A39BF091BA0D6C844EC37C2CBEC
dQy:| AE8EC3501200D7F323EB8181D06C7ACB626C2901D8885053351A07BB9405230A
*/
static ts_ecc_ecdsa_golden st_ecdsa_golden_256 = {
    1,
    {
        0x0377BCC0, 0x26681592, 0x5F3CDF14, 0xC64E5D61, 0xC535C273, 0x637536F7,
        0x19F5BF25, 0x1FDA2156, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xA112ED54, 0xFDAF4EE1, 0x4DC4192F, 0x7C7A9947, 0xF013D563, 0x84335DD3,
        0x3B51E0FC, 0xACEC122D, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xFD11A53D, 0x0AEBFE6D, 0x3694C98E, 0xA3CE7B21, 0x8566A7E8, 0x2DEA7054,
        0x1958A428, 0xC8BDD79F, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xF345B5B5, 0x8926F457, 0xFDAB95A9, 0xBD362686, 0x253EB72A, 0xD33E3511,
        0xB21737AE, 0x2F350F06, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x5313B579, 0x814492C3, 0x135D7EF3, 0xA686FD6E, 0xCED6F8A5, 0x0749A6B2,
        0x151E00C0, 0x338AE2FA, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xC3E79B79, 0x8F335540, 0x684E285C, 0xAAAA74F1, 0x6AE6900E, 0x65455B8E,
        0xE75F70CD, 0x5AF2E9D1, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x3016AC86, 0x50FDF6D9, 0xB69BA98B, 0xC5EC1D8B, 0x9A296177, 0x32F97CCB,
        0xD8565D9D, 0xEC52712F, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x37C2CBEC, 0xD6C844EC, 0xBF091BA0, 0x34901A39, 0xA6155C58, 0x4C23B820,
        0xFF7C546D, 0xB40B89A5, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x9405230A, 0x351A07BB, 0xD8885053, 0x626C2901, 0xD06C7ACB, 0x23EB8181,
        0x1200D7F3, 0xAE8EC350, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
};

/*
e:  | D716F61DFAB94AC331BC3B590687FA301A04EA282822925D3BC61DF9C2F474794769A95F3E212CBF95731A2F6C377225
d:  | 4E2360F7A6A3BED36835ACEEA101DDF187FC8584AF4FF89B381F6BBB1ADEF18BA2EB7130747D7820A6CCD097C33E845E
k:  | E965CC40CA30A38EB98AC656F27628B754CC385D3BC8E1E04FD6AE3915537C53BD00EBD18ADFBEA9A3993713CDA7401D
r:  | 091FCD8941F5D2B8F4CAFF1A6F7BCDB4C170AE1ABDBB484FAF50FBC23E021325D640C457932BEB56405D49A9CCA07778
s:  | BA36DF05A21E43574AA2CAA12F649B0A3895B5BFB56A349981D9ED64DDEE354B894B2A2423DBE58FFFBE8D97073958F9
Qx: | AB61FF2F585B3BF4C4FA540DCB9345AAEC46209FA6409BC0055FC2A523B9802742BC4B93D5EA08F03A1E3D37C55909DE
Qy: | 966305DF268B789F254F676A804351D58A77A73DA821850C5ABA86A564F18B469E28FEC5651DF0183502D321C3BDE2B2
dQx:| 2C3008C802102C634BAF5AFEE83619527D5F646AD0CFC750083E312D2EC3DC4C9E21BA27321FDD608F994593E2D1EEAA
dQy:| 0AF175275287FF0C2405EEF908659544D335117B68D032DA31C7B84BA192557792DD91FFCF98DCD22D439B51A817A3D4
*/
static ts_ecc_ecdsa_golden st_ecdsa_golden_384 = {
    1,
    {
        0x6C377225, 0x95731A2F, 0x3E212CBF, 0x4769A95F, 0xC2F47479, 0x3BC61DF9,
        0x2822925D, 0x1A04EA28, 0x0687FA30, 0x31BC3B59, 0xFAB94AC3, 0xD716F61D,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xC33E845E, 0xA6CCD097, 0x747D7820, 0xA2EB7130, 0x1ADEF18B, 0x381F6BBB,
        0xAF4FF89B, 0x87FC8584, 0xA101DDF1, 0x6835ACEE, 0xA6A3BED3, 0x4E2360F7,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xCDA7401D, 0xA3993713, 0x8ADFBEA9, 0xBD00EBD1, 0x15537C53, 0x4FD6AE39,
        0x3BC8E1E0, 0x54CC385D, 0xF27628B7, 0xB98AC656, 0xCA30A38E, 0xE965CC40,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xCCA07778, 0x405D49A9, 0x932BEB56, 0xD640C457, 0x3E021325, 0xAF50FBC2,
        0xBDBB484F, 0xC170AE1A, 0x6F7BCDB4, 0xF4CAFF1A, 0x41F5D2B8, 0x091FCD89,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0x073958F9, 0xFFBE8D97, 0x23DBE58F, 0x894B2A24, 0xDDEE354B, 0x81D9ED64,
        0xB56A3499, 0x3895B5BF, 0x2F649B0A, 0x4AA2CAA1, 0xA21E4357, 0xBA36DF05,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xC55909DE, 0x3A1E3D37, 0xD5EA08F0, 0x42BC4B93, 0x23B98027, 0x055FC2A5,
        0xA6409BC0, 0xEC46209F, 0xCB9345AA, 0xC4FA540D, 0x585B3BF4, 0xAB61FF2F,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xC3BDE2B2, 0x3502D321, 0x651DF018, 0x9E28FEC5, 0x64F18B46, 0x5ABA86A5,
        0xA821850C, 0x8A77A73D, 0x804351D5, 0x254F676A, 0x268B789F, 0x966305DF,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xE2D1EEAA, 0x8F994593, 0x321FDD60, 0x9E21BA27, 0x2EC3DC4C, 0x083E312D,
        0xD0CFC750, 0x7D5F646A, 0xE8361952, 0x4BAF5AFE, 0x02102C63, 0x2C3008C8,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
    {
        0xA817A3D4, 0x2D439B51, 0xCF98DCD2, 0x92DD91FF, 0xA1925577, 0x31C7B84B,
        0x68D032DA, 0xD335117B, 0x08659544, 0x2405EEF9, 0x5287FF0C, 0x0AF17527,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    },
};

/*
e:  | 00000196D64A68460CB58783668038F833982073C27EADCC5D9D5DF558C7C8DCE2E06D509739DB856647DF10ECA078BD8399583311719D917A150E3980FF61D316A71EA6
d:  | 000001B66603A55BFEE054B3ABE2C670D4D66F9CBB87AE6E532312C1566EB98390C5477EA12F1BE304F3F5841CE2238BC0798708383D73CDDDEA0DB1A1A2B56BB9C74A45
k:  | 0000000BE76A9172A1BCE1A4EBAE6CDA1C118AA659D600BCE3A3916605CAB40CE011D9F9B7DD3E032EEF3DA4EA8423E0A90E12350B30F03EB72D927FB5566156F60AD0D1
r:  | 0000006740F3112A38BF58576192FF1C7B1030E57858991EB9D53CE587AD3F12C9AB0154B809B93E4C430457F15AF44E5155AEC463D191263FD76C8922ACCC14C861AFCC
s:  | 00000025D9604EC838FE3C0997EE24954DC4C0FBAD51AE024F03A001A3D9B1AD332EED7C36F46B645DEED87F24AB73CA547F9F4A40CE3B0B87D347D8773B130ACD988110
Qx: | 00000044F6845CDD12862A005F63D88F87E6EA226D3766B0C9402685CC5AFDDD4BB401CB89769E51D8F5FA8303B837FED80B6E7B809ECBCE4E607F0DE57666EDD5CB665B
Qy: | 00000031D02D5EC1D59343AF76C29DA12D2447A121C04E0C6C714A52A538D160F4E181284279713DFAC2EF411FB7FCB16B1AEA7B0124870F15334CDB0791FEBD206983B3
dQx:| 0000000B9311C0CAF6502EE471DE3A619F21580C543AB05CD12F8A6B3D04EC300AD7A6841A2E04093EAAAF3102DDA57AD6BAF9CD61A64446864645A8E57A9534DA26942E
dQy:| 000001870EA958CACE9B6F535BAD35B4F6706E9B7195EB33F2D7256D1AAD1AA3D7C2BCD4911E6488D61A4EA1BA6F857BD8069F6C7E27350BE1C7E891F5677AA4063E41F4
*/
static ts_ecc_ecdsa_golden st_ecdsa_golden_521 = {
    1,
    {
        0x16A71EA6, 0x80FF61D3, 0x7A150E39, 0x11719D91, 0x83995833, 0xECA078BD,
        0x6647DF10, 0x9739DB85, 0xE2E06D50, 0x58C7C8DC, 0x5D9D5DF5, 0xC27EADCC,
        0x33982073, 0x668038F8, 0x0CB58783, 0xD64A6846, 0x00000196
    },
    {
        0xB9C74A45, 0xA1A2B56B, 0xDDEA0DB1, 0x383D73CD, 0xC0798708, 0x1CE2238B,
        0x04F3F584, 0xA12F1BE3, 0x90C5477E, 0x566EB983, 0x532312C1, 0xBB87AE6E,
        0xD4D66F9C, 0xABE2C670, 0xFEE054B3, 0x6603A55B, 0x000001B6
    },
    {
        0xF60AD0D1, 0xB5566156, 0xB72D927F, 0x0B30F03E, 0xA90E1235, 0xEA8423E0,
        0x2EEF3DA4, 0xB7DD3E03, 0xE011D9F9, 0x05CAB40C, 0xE3A39166, 0x59D600BC,
        0x1C118AA6, 0xEBAE6CDA, 0xA1BCE1A4, 0xE76A9172, 0x0000000B
    },
    {
        0xC861AFCC, 0x22ACCC14, 0x3FD76C89, 0x63D19126, 0x5155AEC4, 0xF15AF44E,
        0x4C430457, 0xB809B93E, 0xC9AB0154, 0x87AD3F12, 0xB9D53CE5, 0x7858991E,
        0x7B1030E5, 0x6192FF1C, 0x38BF5857, 0x40F3112A, 0x00000067
    },
    {
        0xCD988110, 0x773B130A, 0x87D347D8, 0x40CE3B0B, 0x547F9F4A, 0x24AB73CA,
        0x5DEED87F, 0x36F46B64, 0x332EED7C, 0xA3D9B1AD, 0x4F03A001, 0xAD51AE02,
        0x4DC4C0FB, 0x97EE2495, 0x38FE3C09, 0xD9604EC8, 0x00000025
    },
    {
        0xD5CB665B, 0xE57666ED, 0x4E607F0D, 0x809ECBCE, 0xD80B6E7B, 0x03B837FE,
        0xD8F5FA83, 0x89769E51, 0x4BB401CB, 0xCC5AFDDD, 0xC9402685, 0x6D3766B0,
        0x87E6EA22, 0x5F63D88F, 0x12862A00, 0xF6845CDD, 0x00000044
    },
    {
        0x206983B3, 0x0791FEBD, 0x15334CDB, 0x0124870F, 0x6B1AEA7B, 0x1FB7FCB1,
        0xFAC2EF41, 0x4279713D, 0xF4E18128, 0xA538D160, 0x6C714A52, 0x21C04E0C,
        0x2D2447A1, 0x76C29DA1, 0xD59343AF, 0xD02D5EC1, 0x00000031
    },
    {
        0xDA26942E, 0xE57A9534, 0x864645A8, 0x61A64446, 0xD6BAF9CD, 0x02DDA57A,
        0x3EAAAF31, 0x1A2E0409, 0x0AD7A684, 0x3D04EC30, 0xD12F8A6B, 0x543AB05C,
        0x9F21580C, 0x71DE3A61, 0xF6502EE4, 0x9311C0CA, 0x0000000B
    },
    {
        0x063E41F4, 0xF5677AA4, 0xE1C7E891, 0x7E27350B, 0xD8069F6C, 0xBA6F857B,
        0xD61A4EA1, 0x911E6488, 0xD7C2BCD4, 0x1AAD1AA3, 0xF2D7256D, 0x7195EB33,
        0xF6706E9B, 0x5BAD35B4, 0xCE9B6F53, 0x0EA958CA, 0x00000187
    },
};

static void ecc_print(const char *tag, uint32_t data[])
{
    int i = 0;

    printf("%s: | ", tag);
    for (i = 0; i < ECC_SRAM_SIZE_DWORD; i++)
        printf("%08lX", data[ECC_SRAM_SIZE_DWORD - 1 - i]);
    printf("\n");
}

// sample code
static ci_status_t ecc_ecdsa_sign_verify_single_sample(hal_ecc_curve_t curve)
{
    uint8_t u1_key_byte;
    ts_ecc_ecdsa_golden *pt_golden = NULL;
    uint32_t out_r[ECC_SRAM_SIZE_DWORD] = { 0 };
    uint32_t out_s[ECC_SRAM_SIZE_DWORD] = { 0 };
    uint32_t out_v[ECC_SRAM_SIZE_DWORD] = { 0 };

    switch (curve) {
        case HAL_ECC_CURVE_NIST_P_192:
            u1_key_byte = 24;
            pt_golden = &st_ecdsa_golden_192;
            break;
        case HAL_ECC_CURVE_NIST_P_224:
            u1_key_byte = 28;
            pt_golden = &st_ecdsa_golden_224;
            break;
        case HAL_ECC_CURVE_NIST_P_256:
            u1_key_byte = 32;
            pt_golden = &st_ecdsa_golden_256;
            break;
        case HAL_ECC_CURVE_NIST_P_384:
            u1_key_byte = 48;
            pt_golden = &st_ecdsa_golden_384;
            break;
        case HAL_ECC_CURVE_NIST_P_521:
            u1_key_byte = 66;
            pt_golden = &st_ecdsa_golden_521;
            break;
        default:
            printf("wrong mode = %d\n", curve);
            return CI_FAIL;
    }

    EXPECT_NOT_VAL(hal_ecc_init(), 0);

    EXPECT_VAL(hal_ecc_ecdsa_sign(curve, pt_golden->d, pt_golden->k, pt_golden->e,
                                  out_r, out_s), HAL_ECC_STATUS_OK);

    EXPECT_VAL(hal_ecc_ecdsa_verify(curve, out_r, out_s, pt_golden->e,
                                    pt_golden->Qx, pt_golden->Qy, out_v), HAL_ECC_STATUS_OK);
    if (memcmp(out_v, out_r, u1_key_byte)) {
        printf("hal_ecc_ecdsa_verify(curve = %d) failed, u1_key_byte = %d\n", curve, u1_key_byte);

        ecc_print("gold.e  ", pt_golden->e);
        ecc_print("gold.r  ", pt_golden->r);
        ecc_print("gold.s  ", pt_golden->s);
        ecc_print("gold.Qx ", pt_golden->Qx);
        ecc_print("gold.Qy ", pt_golden->Qy);

        ecc_print("out_r   ", out_r);
        ecc_print("out_s   ", out_s);
        ecc_print("out_v   ", out_v);

        return CI_FAIL;
    }

    hal_ecc_deinit();

    return CI_PASS;
}

ci_status_t ci_ecc_ecdsa_sign_verify_sample(void)
{
    hal_ecc_curve_t i = HAL_ECC_CURVE_NIST_P_192;

    for (; i <= HAL_ECC_CURVE_NIST_P_521; i++)
        EXPECT_VAL(ecc_ecdsa_sign_verify_single_sample(i), CI_PASS);

    return CI_PASS;
}


ci_status_t ci_ecc_sample_main(unsigned int portnum)
{
    struct test_entry test_entry_list[] = {
        {"Sample Code: ECC ECDSA sign/verify", ci_ecc_ecdsa_sign_verify_sample},
    };

    return test_execution(test_entry_list, (sizeof(test_entry_list) / sizeof(struct test_entry)));
}
