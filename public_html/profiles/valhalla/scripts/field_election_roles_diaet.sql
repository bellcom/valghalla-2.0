-- phpMyAdmin SQL Dump
-- version 3.4.11.1deb2+deb7u1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Oct 22, 2014 at 08:45 AM
-- Server version: 5.5.38
-- PHP Version: 5.4.4-14+deb7u12

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `db`
--

-- --------------------------------------------------------

--
-- Table structure for table `field_election_roles_diaet`
--

CREATE TABLE IF NOT EXISTS `field_election_roles_diaet` (
  `nid` int(10) unsigned NOT NULL COMMENT 'Primary Key: the node identifier for an election item.',
  `role_diaet_value` mediumtext NOT NULL COMMENT 'Diaet value for each role',
  PRIMARY KEY (`nid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Table for storing the individual role diaet of each...';

--
-- Dumping data for table `field_election_roles_diaet`
--

INSERT INTO `field_election_roles_diaet` (`nid`, `role_diaet_value`) VALUES
(2516, 'a:9:{i:2522;s:1:"1";i:2523;s:1:"1";i:2524;s:1:"1";i:2525;s:1:"1";i:2526;s:1:"1";i:2527;s:1:"1";i:2528;s:1:"1";i:2529;s:1:"1";i:2530;s:1:"1";}'),
(2651, 'a:9:{i:2522;s:1:"1";i:2523;s:1:"1";i:2524;s:1:"1";i:2525;s:1:"1";i:2526;s:1:"1";i:2527;s:1:"1";i:2528;s:1:"1";i:2529;s:1:"1";i:2530;s:1:"1";}'),
(2667, 'a:9:{i:2522;s:2:"11";i:2523;s:1:"1";i:2524;s:1:"1";i:2525;s:1:"1";i:2526;s:1:"1";i:2527;s:1:"1";i:2528;s:1:"1";i:2529;s:1:"1";i:2530;s:1:"1";}');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
