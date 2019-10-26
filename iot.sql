-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jul 18, 2018 at 02:51 AM
-- Server version: 5.5.39
-- PHP Version: 5.4.31

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `iot`
--

-- --------------------------------------------------------

--
-- Table structure for table `aktuator`
--

CREATE TABLE IF NOT EXISTS `aktuator` (
`id` int(11) NOT NULL,
  `nama` varchar(12) NOT NULL,
  `status` enum('ON','OFF') NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `aktuator`
--

INSERT INTO `aktuator` (`id`, `nama`, `status`) VALUES
(1, 'Kipas Angin', 'ON'),
(2, 'Lampu', 'ON'),
(3, 'Proyektor', 'ON');

-- --------------------------------------------------------

--
-- Table structure for table `batas`
--

CREATE TABLE IF NOT EXISTS `batas` (
`id` int(10) NOT NULL,
  `thsuhu` int(10) NOT NULL,
  `thcahaya` int(10) NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `batas`
--

INSERT INTO `batas` (`id`, `thsuhu`, `thcahaya`) VALUES
(1, 8, 25);

-- --------------------------------------------------------

--
-- Table structure for table `kendali`
--

CREATE TABLE IF NOT EXISTS `kendali` (
`id` int(10) NOT NULL,
  `kondisi` enum('AUTO','MANUAL') NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `kendali`
--

INSERT INTO `kendali` (`id`, `kondisi`) VALUES
(1, 'AUTO');

-- --------------------------------------------------------

--
-- Table structure for table `sensor`
--

CREATE TABLE IF NOT EXISTS `sensor` (
`id` int(11) NOT NULL,
  `waktu` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `suhu` int(2) NOT NULL,
  `cahaya` int(5) NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `sensor`
--

INSERT INTO `sensor` (`id`, `waktu`, `suhu`, `cahaya`) VALUES
(1, '2018-07-17 04:52:58', 29, 1000);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `aktuator`
--
ALTER TABLE `aktuator`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `batas`
--
ALTER TABLE `batas`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `kendali`
--
ALTER TABLE `kendali`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor`
--
ALTER TABLE `sensor`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `aktuator`
--
ALTER TABLE `aktuator`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `batas`
--
ALTER TABLE `batas`
MODIFY `id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `kendali`
--
ALTER TABLE `kendali`
MODIFY `id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `sensor`
--
ALTER TABLE `sensor`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
