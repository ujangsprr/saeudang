-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Aug 06, 2021 at 11:10 AM
-- Server version: 10.4.19-MariaDB
-- PHP Version: 8.0.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `saeudang`
--

-- --------------------------------------------------------

--
-- Table structure for table `control_oxg`
--

CREATE TABLE `control_oxg` (
  `token` varchar(50) NOT NULL,
  `ven1` int(1) NOT NULL,
  `ven2` int(1) NOT NULL,
  `ven3` int(1) NOT NULL,
  `ven4` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `control_oxg`
--

INSERT INTO `control_oxg` (`token`, `ven1`, `ven2`, `ven3`, `ven4`) VALUES
('12345', 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `data_oxg`
--

CREATE TABLE `data_oxg` (
  `id` int(11) NOT NULL,
  `hari` text NOT NULL,
  `tanggal` text NOT NULL,
  `kondisi` text NOT NULL,
  `kebutuhan` float NOT NULL,
  `kurang` float NOT NULL,
  `do` float NOT NULL,
  `ds` float NOT NULL,
  `temp` float NOT NULL,
  `presentase` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `data_oxg`
--

INSERT INTO `data_oxg` (`id`, `hari`, `tanggal`, `kondisi`, `kebutuhan`, `kurang`, `do`, `ds`, `temp`, `presentase`) VALUES
(538, 'Friday', '00:20:16(08/06/21)', 'Kurang', 3.7, 2.32, 1.38, 100, 25, 37),
(539, 'Friday', '00:21:06(08/06/21)', 'Kurang', 3.7, 2.42, 1.28, 100, 25, 34),
(540, 'Friday', '00:21:56(08/06/21)', 'Kurang', 3.7, 2.41, 1.29, 100, 25, 34),
(541, 'Friday', '00:26:07(08/06/21)', 'Kurang', 3.7, 2.18, 1.52, 100, 25, 40),
(542, 'Friday', '00:26:57(08/06/21)', 'Kurang', 3.7, 2.23, 1.47, 100, 25, 39),
(543, 'Friday', '00:27:47(08/06/21)', 'Kurang', 3.7, 2.16, 1.54, 100, 25, 41),
(544, 'Friday', '00:28:37(08/06/21)', 'Kurang', 3.7, 2.14, 1.56, 100, 25, 42),
(545, 'Friday', '00:29:27(08/06/21)', 'Kurang', 3.7, 2.19, 1.51, 100, 25, 40),
(546, 'Friday', '00:30:17(08/06/21)', 'Kurang', 3.7, 2.27, 1.43, 100, 25, 38),
(547, 'Friday', '00:31:07(08/06/21)', 'Kurang', 3.7, 2.17, 1.53, 100, 25, 41),
(548, 'Friday', '14:49:19(08/06/21)', 'Bagus', 3.7, 0, 15.13, 100, 25, 100),
(549, 'Friday', '14:50:59(08/06/21)', 'Bagus', 3.7, 0, 9.26, 100, 25, 100),
(550, 'Friday', '14:54:42(08/06/21)', 'Bagus', 3.7, 0, 12.41, 100, 25, 100),
(551, 'Friday', '14:55:32(08/06/21)', 'Bagus', 3.7, 0, 13.29, 100, 25, 100),
(552, 'Friday', '14:56:22(08/06/21)', 'Bagus', 3.7, 0, 14.65, 100, 25, 100),
(553, 'Friday', '14:57:12(08/06/21)', 'Bagus', 3.7, 0, 11.45, 100, 25, 100),
(554, 'Friday', '14:58:02(08/06/21)', 'Bagus', 3.7, 0, 12.81, 100, 25, 100),
(555, 'Friday', '14:58:52(08/06/21)', 'Bagus', 3.7, 0, 14.52, 100, 25, 100),
(556, 'Friday', '14:59:42(08/06/21)', 'Kurang', 3.7, 3.7, 0, 100, 25, 0),
(557, 'Friday', '15:00:32(08/06/21)', 'Bagus', 3.7, 0, 7.88, 100, 25, 100),
(558, 'Friday', '15:01:22(08/06/21)', 'Bagus', 3.7, 0, 5.49, 100, 25, 100),
(559, 'Friday', '15:02:12(08/06/21)', 'Bagus', 3.7, 0, 8.91, 100, 25, 100),
(560, 'Friday', '15:04:01(08/06/21)', 'Bagus', 3.7, 0, 21.27, 100, 25, 100),
(561, 'Friday', '15:05:20(08/06/21)', 'Bagus', 3.7, 0, 7.6, 100, 25, 100),
(562, 'Friday', '15:06:10(08/06/21)', 'Bagus', 3.7, 0, 5.79, 100, 25, 100),
(563, 'Friday', '15:07:00(08/06/21)', 'Bagus', 3.7, 0, 10.82, 100, 25, 100),
(564, 'Friday', '15:07:50(08/06/21)', 'Bagus', 3.7, 0, 8.1, 100, 25, 100),
(565, 'Friday', '15:08:40(08/06/21)', 'Bagus', 3.7, 0, 9.26, 100, 25, 100),
(566, 'Friday', '15:10:19(08/06/21)', 'Bagus', 3.7, 0, 7.28, 100, 25, 100),
(567, 'Friday', '15:12:42(08/06/21)', 'Bagus', 3.7, 0, 7.98, 100, 25, 100),
(568, 'Friday', '15:13:32(08/06/21)', 'Bagus', 3.7, 0, 7.68, 100, 25, 100),
(569, 'Friday', '15:14:22(08/06/21)', 'Bagus', 3.7, 0, 5.64, 100, 25, 100),
(570, 'Friday', '15:15:52(08/06/21)', 'Bagus', 3.7, 0, 5.89, 100, 25, 100),
(571, 'Friday', '15:16:42(08/06/21)', 'Bagus', 3.7, 0, 10.54, 100, 25, 100),
(572, 'Friday', '15:17:32(08/06/21)', 'Bagus', 3.7, 0, 10.42, 100, 25, 100),
(573, 'Friday', '15:19:53(08/06/21)', 'Bagus', 3.7, 0, 14.1, 100, 25, 100),
(574, 'Friday', '15:20:43(08/06/21)', 'Bagus', 3.7, 0, 9.26, 100, 25, 100),
(575, 'Friday', '15:21:33(08/06/21)', 'Kurang', 3.7, 3.7, 0, 100, 25, 0),
(576, 'Friday', '15:22:23(08/06/21)', 'Bagus', 3.7, 0, 8.53, 100, 25, 100),
(577, 'Friday', '15:23:13(08/06/21)', 'Bagus', 3.7, 0, 7.15, 100, 25, 100),
(578, 'Friday', '15:24:03(08/06/21)', 'Bagus', 3.7, 0, 10.17, 100, 25, 100),
(579, 'Friday', '15:24:53(08/06/21)', 'Bagus', 3.7, 0, 12.23, 100, 25, 100),
(580, 'Friday', '15:25:43(08/06/21)', 'Bagus', 3.7, 0, 13.57, 100, 25, 100),
(581, 'Friday', '15:26:33(08/06/21)', 'Bagus', 3.7, 0, 14.1, 100, 25, 100),
(582, 'Friday', '15:39:38(08/06/21)', 'Bagus', 3.7, 0, 12.64, 100, 25, 100),
(583, 'Friday', '15:40:28(08/06/21)', 'Bagus', 3.7, 0, 14.55, 100, 25, 100),
(584, 'Friday', '15:41:18(08/06/21)', 'Bagus', 3.7, 0, 15.48, 100, 25, 100),
(585, 'Friday', '15:42:08(08/06/21)', 'Bagus', 3.7, 0, 14.58, 100, 25, 100),
(586, 'Friday', '15:42:58(08/06/21)', 'Bagus', 3.7, 0, 14.02, 100, 25, 100),
(587, 'Friday', '15:43:48(08/06/21)', 'Bagus', 3.7, 0, 15.23, 100, 25, 100),
(588, 'Friday', '15:44:38(08/06/21)', 'Bagus', 3.7, 0, 14.98, 100, 25, 100),
(589, 'Friday', '15:45:28(08/06/21)', 'Bagus', 3.7, 0, 16.18, 100, 25, 100),
(590, 'Friday', '15:46:18(08/06/21)', 'Bagus', 3.7, 0, 16.49, 100, 25, 100),
(591, 'Friday', '15:47:08(08/06/21)', 'Bagus', 3.7, 0, 13.69, 100, 25, 100),
(592, 'Friday', '15:47:58(08/06/21)', 'Bagus', 3.7, 0, 12.56, 100, 25, 100),
(593, 'Friday', '15:48:48(08/06/21)', 'Bagus', 3.7, 0, 16.54, 100, 25, 100),
(594, 'Friday', '15:49:38(08/06/21)', 'Bagus', 3.7, 0, 16.26, 100, 25, 100);

-- --------------------------------------------------------

--
-- Table structure for table `day_oxg`
--

CREATE TABLE `day_oxg` (
  `id` int(11) NOT NULL,
  `hari` text NOT NULL,
  `do` float NOT NULL,
  `ds` float NOT NULL,
  `temp` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `day_oxg`
--

INSERT INTO `day_oxg` (`id`, `hari`, `do`, `ds`, `temp`) VALUES
(1, 'Senin', 4.5, 300, 25),
(2, 'Selasa', 4.5, 300, 25),
(3, 'Rabu', 4, 257, 24),
(4, 'Kamis', 3.8, 310, 26),
(5, 'Jumat', 4.5, 312, 25),
(6, 'Sabtu', 4.3, 289, 26),
(7, 'Minggu', 4.6, 320, 25);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `data_oxg`
--
ALTER TABLE `data_oxg`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `day_oxg`
--
ALTER TABLE `day_oxg`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `data_oxg`
--
ALTER TABLE `data_oxg`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=595;

--
-- AUTO_INCREMENT for table `day_oxg`
--
ALTER TABLE `day_oxg`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
