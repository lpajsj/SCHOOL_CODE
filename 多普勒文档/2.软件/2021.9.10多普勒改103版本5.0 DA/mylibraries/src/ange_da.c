#include "ange_da.h"
#include "ange_timg.h"
//u16 da_shuju1[64]={496,544,592,639,685,729,771,810,846,879,908,933,954,970,982,989,991,989,982,970,
//	954,933,908,879,846,810,771,729,685,639,592,544,496,447,399,352,306,262,220,181,145,112,83,58,37,
//21,9,2,0,2,9,21,37,58,83,112,145,181,220,262,306,352,399,447};
u16 da_shuju1[1024]={528,530,532,534,536,538,540,542,544,546,548,550,552,554,556,558,560,562,
	564,566,568,570,572,574,576,578,580,582,584,586,588,590,592,594,596,598,600,602,604,606,608,610,
	612,614,616,618,620,622,624,626,628,630,632,634,636,638,640,642,644,646,648,650,652,654,656,658,
	660,662,664,666,668,670,672,674,676,678,680,682,684,686,688,690,692,694,696,698,700,702,704,706,
	708,710,712,714,716,718,720,722,724,726,728,730,732,734,736,738,740,742,744,746,748,750,752,754,
	756,758,760,762,764,766,768,770,772,774,776,778,780,782,784,786,788,790,792,794,796,798,800,802,
	804,806,808,810,812,814,816,818,820,822,824,826,828,830,832,834,836,838,840,842,844,846,848,850,
	852,854,856,858,860,862,864,866,868,870,872,874,876,878,880,882,884,886,888,890,892,894,896,898,
	900,902,904,906,908,910,912,914,916,918,920,922,924,926,928,930,932,934,936,938,940,942,944,946,
	948,950,952,954,956,958,960,962,964,966,968,970,972,974,976,978,980,982,984,986,988,990,992,994,
	996,998,1000,1002,1004,1006,1008,1010,1012,1014,1016,1018,1020,1022,1024,1026,1028,1030,1032,1034,
	1036,1038,1040,1042,1044,1046,1048,1050,1052,1054,1056,1058,1060,1062,1064,1066,1068,1070,1072,1074,
	1076,1078,1080,1082,1084,1086,1088,1090,1092,1094,1096,1098,1100,1102,1104,1106,1108,1110,1112,1114,
	1116,1118,1120,1122,1124,1126,1128,1130,1132,1134,1136,1138,1140,1142,1144,1146,1148,1150,1152,1154
	,1156,1158,1160,1162,1164,1166,1168,1170,1172,1174,1176,1178,1180,1182,1184,1186,1188,1190,1192,1194,
	1196,1198,1200,1202,1204,1206,1208,1210,1212,1214,1216,1218,1220,1222,1224,1226,1228,1230,1232,1234,
	1236,1238,1240,1242,1244,1246,1248,1250,1252,1254,1256,1258,1260,1262,1264,1266,1268,1270,1272,1274,
	1276,1278,1280,1282,1284,1286,1288,1290,1292,1294,1296,1298,1300,1302,1304,1306,1308,1310,1312,1314,
	1316,1318,1320,1322,1324,1326,1328,1330,1332,1334,1336,1338,1340,1342,1344,1346,1348,1350,1352,1354,
	1356,1358,1360,1362,1364,1366,1368,1370,1372,1374,1376,1378,1380,1382,1384,1386,1388,1390,1392,1394,
	1396,1398,1400,1402,1404,1406,1408,1410,1412,1414,1416,1418,1420,1422,1424,1426,1428,1430,1432,1434,
	1436,1438,1440,1442,1444,1446,1448,1450,1452,1454,1456,1458,1460,1462,1464,1466,1468,1470,1472,1474,1476,1478,1480,1482,1484,1486,1488,1490,1492,1494,1496,1498,
	1500,1502,1504,1506,1508,1510,1512,1514,1516,1518,1520,1522,1524,1526,1528,1530,1532,1534,1536,1538,1540,1542,1544,1546,1548,1550,1552,1554,1556,1558,1560,1562,1564,
	1566,1568,1570,1572,1574,1576,1578,1580,1582,1584,1586,1588,1590,1592,1594,1596,1598,1600,1602,1604,1606,1608,1610,1612,1614,1616,1618,1620,1622,1624,1626,1628,1630,
	1632,1634,1636,1638,1640,1642,1644,1646,1648,1650,1652,1654,1656,1658,1660,1662,1664,1666,1668,1670,1672,1674,1676,1678,1680,1682,1684,1686,1688,1690,1692,1694,1696,
	1698,1700,1702,1704,1706,1708,1710,1712,1714,1716,1718,1720,1722,1724,1726,1728,1730,1732,1734,1736,1738,1740,1742,1744,1746,1748,1750,1752,1754,1756,1758,1760,1762,
	1764,1766,1768,1770,1772,1774,1776,1778,1780,1782,1784,1786,1788,1790,1792,1794,1796,1798,1800,1802,1804,1806,1808,1810,1812,1814,1816,1818,1820,1822,1824,1826,1828,
	1830,1832,1834,1836,1838,1840,1842,1844,1846,1848,1850,1852,1854,1856,1858,1860,1862,1864,1866,1868,1870,1872,1874,1876,1878,1880,1882,1884,1886,1888,1890,1892,1894,
	1896,1898,1900,1902,1904,1906,1908,1910,1912,1914,1916,1918,1920,1922,1924,1926,1928,1930,1932,1934,1936,1938,1940,1942,1944,1946,1948,1950,1952,1954,1956,1958,1960,
	1962,1964,1966,1968,1970,1972,1974,1976,1978,1980,1982,1984,1986,1988,1990,1992,1994,1996,1998,2000,2002,2004,2006,2008,2010,2012,2014,2016,2018,2020,2022,2024,2026,
	2028,2030,2032,2034,2036,2038,2040,2042,2044,2046,2048,2050,2052,2054,2056,2058,2060,2062,2064,2066,2068,2070,2072,2074,2076,2078,2080,2082,2084,2086,2088,2090,2092
	,2094,2096,2098,2100,2102,2104,2106,2108,2110,2112,2114,2116,2118,2120,2122,2124,2126,2128,2130,2132,2134,2136,2138,2140,2142,2144,2146,2148,2150,2152,2154,2156,2158,
	2160,2162,2164,2166,2168,2170,2172,2174,2176,2178,2180,2182,2184,2186,2188,2190,2192,2194,2196,2198,2200,2202,2204,2206,2208,2210,2212,2214,2216,2218,2220,2222,2224,
	2226,2228,2230,2232,2234,2236,2238,2240,2242,2244,2246,2248,2250,2252,2254,2256,2258,2260,2262,2264,2266,2268,2270,2272,2274,2276,2278,2280,2282,2284,2286,2288,2290,
	2292,2294,2296,2298,2300,2302,2304,2306,2308,2310,2312,2314,2316,2318,2320,2322,2324,2326,2328,2330,2332,2334,2336,2338,2340,2342,2344,2346,2348,2350,2352,2354,2356,
	2358,2360,2362,2364,2366,2368,2370,2372,2374,2376,2378,2380,2382,2384,2386,2388,2390,2392,2394,2396,2398,2400,2402,2404,2406,2408,2410,2412,2414,2416,2418,2420,2422,
	2424,2426,2428,2430,2432,2434,2436,2438,2440,2442,2444,2446,2448,2450,2452,2454,2456,2458,2460,2462,2464,2466,2468,2470,2472,2474,2476,2478,2480,2482,2484,2486,2488,
	2490,2492,2494,2496,2498,2500,2502,2504,2506,2508,2510,2512,2514,2516,2518,2520,2522,2524,2526,2528,2530,2532,2534,2536,2538,2540,2542,2544,2546,2548,2550,2552,2554,
2556,2558,2560,2562,2564,2566,2568,2570,2572,2574};
void ange_DA_GPIO_Config()  //adc通道11 pc1的端口初始化
{
	GPIO_InitTypeDef gpioinit;
	ange_DA_GPIO_APBxClock(ange_DA_GPIO_CLK,ENABLE);
	gpioinit.GPIO_Mode=GPIO_Mode_AIN;
	gpioinit.GPIO_Pin=ange_DA1_GPIO_Pin  ;
	gpioinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(ange_DA_GPIO_PORT,&gpioinit);
	return;
}
u16 ange_DA_TIM_Period=ange_TIMg_Period;   //
u16 ange_DA_TIM_Prescaler=ange_TIMg_Prescaler;  //分频可以到；0
void ange_DA_Config()
{
	DAC_InitTypeDef dacinit;
	ange_DA_APBxClock(ange_DA_CLK,ENABLE);
	//DAC_LFSRUnmask_Bit相当于在选有几位数据在波动以DA寄存器数据为最小值（0bit是一位），DAC_TriangleAmplitude三角波的幅度以DA数据为最小值，每次触发加一
	dacinit.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	dacinit.DAC_OutputBuffer=DAC_OutputBuffer_Enable;            //输出缓冲，减小输出阻抗
	dacinit.DAC_Trigger=DAC_Trigger_None;                      //外部触发使能后不能修改触发方式，另外软件触发更快
	dacinit.DAC_WaveGeneration=DAC_WaveGeneration_None;            //无 噪声 三角波//
	DAC_Init(ange_DA_Channel1,&dacinit);
	DAC_Cmd(ange_DA_Channel1,ENABLE);
}
void ange_DA_DMA_nvic_init()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //设置中断优先级分组
	nvicinit.NVIC_IRQChannel=ange_DA_DMA_IRQn;       //中断源选择
	nvicinit.NVIC_IRQChannelPreemptionPriority=1; //设置抢占优先级
	nvicinit.NVIC_IRQChannelSubPriority=1;       //设置子优先级
	nvicinit.NVIC_IRQChannelCmd=ENABLE;          //中断使能
	NVIC_Init(&nvicinit);           //nvic初始化函数
}
void ange_DA_DMA_IRQnHandler()
{
	if(DMA_GetITStatus(DMA2_IT_TC4)==SET)
	{
		DMA_ClearITPendingBit(DMA2_IT_TC4);
		TIM_Cmd(ange_DA_TIMx,DISABLE);
	}
}
void ange_DA_DMA_Config(u16* y)
{
	DMA_InitTypeDef dmainit;
	RCC_AHBPeriphClockCmd(ange_DA_DMA_Clock,ENABLE);
	dmainit.DMA_DIR=DMA_DIR_PeripheralDST;  //SRC 外设到存储器 DST 存到外
	dmainit.DMA_PeripheralBaseAddr=ange_DA_DMA_mudi;
	dmainit.DMA_MemoryBaseAddr=(u32)y;
	dmainit.DMA_BufferSize=ange_DA_DMA_BufferSize;
	dmainit.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	dmainit.DMA_MemoryInc=DMA_MemoryInc_Enable;
	dmainit.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	dmainit.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
//	dmainit.DMA_Mode=DMA_Mode_Normal;
	dmainit.DMA_Mode=DMA_Mode_Circular;
	dmainit.DMA_Priority=DMA_Priority_Medium;
	dmainit.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(ange_DA_DMA_Channel,&dmainit);
	DMA_Cmd(ange_DA_DMA_Channel,ENABLE);
	DAC_DMACmd(ange_DA_Channel1,ENABLE);

}
void ange_DA_TIM_Config()
{
	ange_DA_TIM_APBxClock(ange_DA_TIM_CLK,ENABLE);
	TIM_TimeBaseInitTypeDef timinit;
	timinit.TIM_ClockDivision=0;
	timinit.TIM_CounterMode=TIM_CounterMode_Up;
	timinit.TIM_Period=ange_DA_TIM_Period;
	timinit.TIM_Prescaler=ange_DA_TIM_Prescaler;
	timinit.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(ange_DA_TIMx,&timinit);
	TIM_SelectOutputTrigger(ange_DA_TIMx,TIM_TRGOSource_Update);
	//变为从模式由TIM1触发转换开始
//	TIM_SelectSlaveMode(ange_DA_TIMx,TIM_SlaveMode_Trigger);
	//
	TIM_Cmd(ange_DA_TIMx,ENABLE);
}
void ange_DA_init()
{
	ange_DA_GPIO_Config();  //adc通道11 pc1的端口初始化
	ange_DA_Config();
//	ange_DA_TIM_Config();
}
//初始化,时调用	ange_DA_init();//DA初始化
	              //ange_DA_DMA_Config(da_shuju1);//DMA初始化	
void dapinlv(u32 i)//产生正弦波,输入参数为频率
{
	  double  x;
		uint32_t t;
		x=1125000/i;  //最低HZ
		t=(u32)x-1;
		ange_DA_TIM_Period=t+5;
	 TIM_SetAutoreload(ange_DA_TIMx,ange_DA_TIM_Period);
//		ange_DA_TIM_Config();
}
