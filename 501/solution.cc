#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include <primesieve.hpp>

typedef long long ll;

const ll N = 1'000'000'000'000;
const std::map<ll, ll> precomputed_primepi{
    { 166666666666, 6721737844 },
    { 125000000000, 5100605440 },
    { 100000000000, 4118054813 },
    { 71428571428, 2982886200 },
    { 66666666666, 2792083254 },
    { 47619047619, 2022912176 },
    { 45454545454, 1934795132 },
    { 38461538461, 1648886461 },
    { 37037037037, 1590395560 },
    { 30303030303, 1312566404 },
    { 29411764705, 1275613868 },
    { 28571428571, 1240730613 },
    { 26315789473, 1146883174 },
    { 25641025641, 1118745170 },
    { 21739130434, 955402619 },
    { 19607843137, 865666513 },
    { 18181818181, 805400321 },
    { 17543859649, 778376407 },
    { 17241379310, 765549015 },
    { 16129032258, 718291358 },
    { 15384615384, 686586632 },
    { 14492753623, 648516511 },
    { 13513513513, 606601816 },
    { 12987012987, 584012797 },
    { 12195121951, 549960714 },
    { 11764705882, 531414494 },
    { 11627906976, 525512675 },
    { 11494252873, 519742693 },
    { 10989010989, 497912792 },
    { 10752688172, 487687104 },
    { 10638297872, 482733556 },
    { 10526315789, 477881874 },
    { 9433962264, 430437352 },
    { 9009009009, 411916421 },
    { 8695652173, 398235210 },
    { 8474576271, 388570039 },
    { 8403361344, 385455288 },
    { 8196721311, 376406348 },
    { 8130081300, 373486693 },
    { 8000000000, 367783654 },
    { 7751937984, 356896207 },
    { 7518796992, 346653520 },
    { 7462686567, 344185493 },
    { 7092198581, 327871034 },
    { 7042253521, 325668242 },
    { 6993006993, 323495678 },
    { 6896551724, 319239105 },
    { 6849315068, 317154525 },
    { 6451612903, 299570086 },
    { 6329113924, 294146186 },
    { 6289308176, 292382396 },
    { 6211180124, 288918607 },
    { 6024096385, 280615053 },
    { 5649717514, 263966976 },
    { 5617977528, 262552989 },
    { 5464480874, 255711097 },
    { 5405405405, 253075297 },
    { 5347593582, 250495029 },
    { 5154639175, 241874457 },
    { 4975124378, 233841159 },
    { 4950495049, 232737931 },
    { 4926108374, 231645330 },
    { 4878048780, 229491395 },
    { 4854368932, 228429975 },
    { 4784688995, 225304982 },
    { 4694835680, 221272132 },
    { 4672897196, 220285964 },
    { 4651162790, 219310276 },
    { 4608294930, 217384146 },
    { 4587155963, 216433767 },
    { 4566210045, 215492312 },
    { 4524886877, 213633879 },
    { 4424778761, 209129438 },
    { 4255319148, 201492046 },
    { 4219409282, 199872482 },
    { 4048582995, 192157735 },
    { 4016064257, 190687731 },
    { 3952569169, 187816246 },
    { 3937007874, 187111461 },
    { 3861003861, 183670322 },
    { 3816793893, 181667812 },
    { 3773584905, 179708693 },
    { 3745318352, 178426971 },
    { 3649635036, 174083030 },
    { 3597122302, 171696563 },
    { 3484320557, 166565694 },
    { 3436426116, 164384690 },
    { 3389830508, 162261994 },
    { 3355704697, 160706800 },
    { 3344481605, 160195105 },
    { 3322259136, 159181695 },
    { 3311258278, 158679491 },
    { 3300330033, 158180906 },
    { 3278688524, 157193631 },
    { 3236245954, 155256432 },
    { 3184713375, 152902220 },
    { 3134796238, 150620143 },
    { 3115264797, 149726616 },
    { 3095975232, 148844482 },
    { 3067484662, 147540712 },
    { 3058103975, 147110949 },
    { 3039513677, 146259321 },
    { 2994011976, 144175787 },
    { 2985074626, 143765863 },
    { 2949852507, 142151503 },
    { 2932551319, 141357909 },
    { 2915451895, 140573117 },
    { 2890173410, 139413185 },
    { 2816901408, 136047242 },
    { 2793296089, 134962117 },
    { 2762430939, 133542471 },
    { 2739726027, 132498454 },
    { 2695417789, 130459051 },
    { 2652519893, 128482435 },
    { 2624671916, 127199617 },
    { 2617801047, 126882583 },
    { 2590673575, 125631853 },
    { 2557544757, 124102220 },
    { 2544529262, 123500972 },
    { 2538071065, 123202890 },
    { 2531645569, 122905782 },
    { 2512562814, 122023898 },
    { 2481389578, 120583806 },
    { 2457002457, 119455910 },
    { 2433090024, 118349760 },
    { 2421307506, 117804228 },
    { 2409638554, 117264310 },
    { 2398081534, 116729474 },
    { 2369668246, 115413765 },
    { 2341920374, 114128394 },
    { 2288329519, 111643272 },
    { 2247191011, 109732521 },
    { 2242152466, 109498352 },
    { 2237136465, 109265632 },
    { 2217294900, 108343596 },
    { 2207505518, 107888720 },
    { 2202643171, 107662826 },
    { 2183406113, 106768590 },
    { 2145922746, 105024875 },
    { 2132196162, 104385882 },
    { 2123142250, 103964930 },
    { 2114164904, 103547105 },
    { 2092050209, 102516304 },
    { 2079002079, 101908152 },
    { 2074688796, 101707044 },
    { 2061855670, 101108724 },
    { 2044989775, 100322554 },
    { 2028397565, 99548516 },
    { 2012072434, 98786560 },
    { 1996007984, 98036153 },
    { 1992031872, 97850435 },
    { 1980198019, 97297773 },
    { 1956947162, 96211235 },
    { 1945525291, 95676924 },
    { 1941747572, 95500198 },
    { 1934235976, 95149205 },
    { 1926782273, 94800333 },
    { 1901140684, 93601435 },
    { 1897533206, 93432215 },
    { 1876172607, 92432156 },
    { 1869158878, 92103680 },
    { 1862197392, 91777752 },
    { 1858736059, 91615885 },
    { 1845018450, 90973197 },
    { 1841620626, 90813788 },
    { 1834862385, 90497072 },
    { 1814882032, 89560322 },
    { 1808318264, 89252533 },
    { 1805054151, 89099387 },
    { 1788908765, 88341218 },
    { 1779359430, 87892988 },
    { 1769911504, 87449384 },
    { 1766784452, 87302699 },
    { 1745200698, 86288554 },
    { 1727115716, 85438926 },
    { 1721170395, 85159484 },
    { 1715265866, 84881376 },
    { 1706484641, 84468339 },
    { 1697792869, 84059353 },
    { 1692047377, 83789151 },
    { 1675041876, 82988228 },
    { 1636661211, 81180981 },
    { 1628664495, 80803514 },
    { 1607717041, 79816135 },
    { 1605136436, 79694265 },
    { 1597444089, 79331221 },
    { 1589825119, 78971722 },
    { 1579778830, 78497390 },
    { 1577287066, 78379446 },
    { 1574803149, 78262106 },
    { 1540832049, 76657645 },
    { 1526717557, 75990333 },
    { 1510574018, 75226798 },
    { 1499250374, 74691039 },
    { 1494768310, 74478886 },
    { 1490312965, 74267410 },
    { 1483679525, 73953195 },
    { 1472754050, 73435440 },
    { 1468428781, 73230692 },
    { 1459854014, 72824395 },
    { 1455604075, 72622970 },
    { 1451378809, 72422711 },
    { 1440922190, 71926905 },
    { 1438848920, 71828479 },
    { 1434720229, 71632874 },
    { 1432664756, 71535497 },
    { 1430615164, 71438188 },
    { 1422475106, 71052037 },
    { 1416430594, 70765048 },
    { 1414427157, 70670043 },
    { 1402524544, 70105094 },
    { 1394700139, 69733739 },
    { 1392757660, 69641646 },
    { 1386962552, 69366095 },
    { 1383125864, 69184076 },
    { 1367989056, 68465013 },
    { 1362397820, 68199284 },
    { 1356852103, 67935456 },
    { 1342281879, 67242104 },
    { 1340482573, 67156179 },
    { 1335113484, 66900815 },
    { 1328021248, 66562940 },
    { 1324503311, 66395443 },
    { 1319261213, 66145989 },
    { 1310615989, 65734615 },
    { 1305483028, 65489705 },
    { 1303780964, 65408555 },
    { 1297016861, 65086371 },
    { 1285347043, 64530189 },
    { 1283697047, 64451652 },
    { 1280409731, 64295099 },
    { 1273885350, 63983845 },
    { 1267427122, 63675454 },
    { 1264222503, 63522558 },
    { 1261034047, 63370274 },
    { 1259445843, 63294530 },
    { 1251564455, 62918562 },
    { 1246882793, 62694663 },
    { 1245330012, 62620325 },
    { 1239157372, 62325936 },
    { 1230012300, 61888926 },
    { 1226993865, 61744729 },
    { 1223990208, 61601636 },
    { 1222493887, 61530166 },
    { 1203369434, 60615526 },
    { 1197604790, 60339934 },
    { 1193317422, 60134957 },
    { 1187648456, 59863702 },
    { 1186239620, 59796194 },
    { 1177856301, 59395448 },
    { 1175088131, 59262916 },
    { 1160092807, 58544197 },
    { 1156069364, 58351500 },
    { 1154734411, 58287502 },
    { 1150747986, 58096275 },
    { 1148105625, 57969455 },
    { 1138952164, 57531131 },
    { 1137656427, 57468796 },
    { 1128668171, 57038465 },
    { 1124859392, 56855653 },
    { 1119820828, 56614062 },
    { 1117318435, 56493942 },
    { 1113585746, 56314871 },
    { 1112347052, 56255516 },
    { 1109877913, 56137007 },
    { 1104972375, 55901378 },
    { 1095290251, 55436091 },
    { 1094091903, 55378598 },
    { 1090512540, 55206419 },
    { 1085776330, 54978754 },
    { 1084598698, 54922089 },
    { 1083423618, 54865532 },
    { 1079913606, 54696493 },
    { 1071811361, 54307370 },
    { 1070663811, 54251926 },
    { 1064962726, 53977449 },
    { 1060445387, 53759978 },
    { 1053740779, 53437438 },
    { 1051524710, 53330872 },
    { 1047120418, 53119023 },
    { 1043841336, 52961341 },
    { 1042752867, 52908958 },
    { 1036269430, 52596219 },
    { 1027749229, 52185777 },
    { 1026694045, 52135161 },
    { 1021450459, 51882344 },
    { 1018329938, 51731963 },
    { 1015228426, 51582283 },
    { 1011122345, 51384104 },
    { 1007049345, 51187597 },
    { 1005025125, 51089876 },
    { 1002004008, 50944137 },
};
const ll precompute_limit = 1'000'000'000;
std::vector<ll> primes;

ll primepi(ll n)
{
    if (n > precompute_limit) {
        auto it = precomputed_primepi.find(n);
        if (it != precomputed_primepi.end()) {
            return it->second;
        } else {
            std::cerr << "primepi(" << n << ") not precomputed" << std::endl;
            std::exit(1);
        }
    }
    return std::upper_bound(primes.begin(), primes.end(), n) - primes.begin();
}

ll count()
{
    ll c = 0;
    ll cube_root_count = primepi(std::cbrt(N));
    // ll quartic_root_count = primepi(std::pow(N, 1.0 / 4));
    ll septic_root_count = primepi(std::pow(N, 1.0 / 7));
    for (size_t i = 0; i < cube_root_count; ++i) {
        ll p = primes[i];
        ll j_bound = primepi(std::sqrt(double(N) / p));
        for (size_t j = i + 1; j < j_bound; ++j) {
            ll q = primes[j];
            // std::cout << p << " " << q << " " << primepi(N / (p * q)) << " " << primepi(N / (p * q)) - j - 1 << std::endl;
            c += primepi(N / (p * q)) - j - 1;
        }
    }
    for (size_t i = 0; i < cube_root_count; ++i) {
        ll p = primes[i];
        ll max_q = N / (p * p * p);
        c += primepi(N / (p * p * p)) - (1 ? p <= max_q : 0);
    }
    c += septic_root_count;
    return c;
}

int main()
{
    primesieve::generate_primes(precompute_limit, &primes);
    std::cout << count() << std::endl;
    return 0;
}