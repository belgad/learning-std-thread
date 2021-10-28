# Efficiency #

## specs ##

* CPU: `Intel(R) Core(TM) i7-10700K CPU @ 3.80GHz 8C/16T`
* RAM: `32GB DDR4 2400MHz Lat: 16-18-18-32`
* OS: `Windows 11 Pro Insider Preview 22483.1011`
* Build: `mkdir cmake-build-release && cd cmake-build-release && cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" .. && cmake --build .`
* Number of tests: `1`

## pi ##

| thread number | interval number | mean sequence time | mean parallel time | mean efficiency |
| ------------- | --------------- | -----------------: | -----------------: | --------------- |
| 8             | 10^7            |           10998 us |            1998 us | 5.504504        |
| 8             | 10^8            |          111802 us |           22255 us | 5.023680        |
| 8             | 10^9            |         1102292 us |          200070 us | 5.509531        |
| 16            | 10^7            |           11002 us |            1999 us | 5.503751        |
| 16            | 10^8            |          111934 us |           17001 us | 6.583965        |
| 16            | 10^9            |         1104298 us |          147359 us | 7.493929        |
| 32            | 10^7            |           10998 us |            1999 us | 5.501750        |
| 32            | 10^8            |           97902 us |           15998 us | 6.119639        |
| 32            | 10^9            |         1107413 us |          134227 us | 8.250299        |

## matrix product ##

| thread number | size | mean sequence time | mean parallel time | mean efficiency |
| ------------- | ---- | -----------------: | -----------------: | --------------- |
| 8             | 500  |           92257 us |           23737 us | 3.886632        |
| 8             | 1000 |         1239993 us |          360676 us | 3.437969        |
| 8             | 1500 |         9089269 us |         2176030 us | 4.176996        |
| 8             | 2000 |        40351322 us |         7612534 us | 5.300642        |
| 16            | 500  |           79841 us |           33708 us | 2.368606        |
| 16            | 1000 |         1181602 us |          510281 us | 2.315590        |
| 16            | 1500 |         9256565 us |         2136264 us | 4.333062        |
| 16            | 2000 |        40359315 us |         5705703 us | 7.073504        |
| 32            | 500  |           89153 us |           22812 us | 3.908162        |
| 32            | 1000 |         1289564 us |          430794 us | 2.993458        |
| 32            | 1500 |         9342523 us |         2049400 us | 4.558662        |
| 32            | 2000 |        40384907 us |         5391661 us | 7.490253        |
