-- phpMyAdmin SQL Dump
-- version 3.5.8.2
-- http://www.phpmyadmin.net
--
-- Host: sql109.byetcluster.com
-- Generato il: Giu 27, 2015 alle 11:36
-- Versione del server: 5.00.15
-- Versione PHP: 5.3.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `b22_16357055_test`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `setpoint`
--

CREATE TABLE IF NOT EXISTS `setpoint` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'unique ID',
  `event` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Event Date and Time',
  `analog0` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `analog1` varchar(30) COLLATE utf32_unicode_ci NOT NULL COMMENT 'Unique ID of thevalueset',
  `analog2` varchar(30) COLLATE utf32_unicode_ci NOT NULL COMMENT 'Measured Temperature in units',
  `analog3` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `analog4` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `analog5` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `digital0` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `digital1` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `digital2` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `digital3` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `digital4` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `pwm0` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `pwm1` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `pwm2` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  KEY `event` (`event`,`analog1`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf32 COLLATE=utf32_unicode_ci AUTO_INCREMENT=2 ;

--
-- Dump dei dati per la tabella `setpoint`
--

INSERT INTO `setpoint` (`id`, `event`, `analog0`, `analog1`, `analog2`, `analog3`, `analog4`, `analog5`, `digital0`, `digital1`, `digital2`, `digital3`, `digital4`, `pwm0`, `pwm1`, `pwm2`) VALUES
(1, '2015-06-18 00:00:00', '19364', '-26898', '-7524', '370', '44', '280', '1', '1', '1', '0', '0', '19363', '48', '-26900');

-- --------------------------------------------------------

--
-- Struttura della tabella `temperature`
--

CREATE TABLE IF NOT EXISTS `temperature` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'unique ID',
  `event` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Event Date and Time',
  `sensor` varchar(30) COLLATE utf32_unicode_ci NOT NULL COMMENT 'Unique ID of the sensor',
  `celsius` varchar(10) COLLATE utf32_unicode_ci NOT NULL COMMENT 'Measured Temperature in Celsius',
  PRIMARY KEY (`id`),
  KEY `event` (`event`,`sensor`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf32 COLLATE=utf32_unicode_ci AUTO_INCREMENT=7 ;

--
-- Dump dei dati per la tabella `temperature`
--

INSERT INTO `temperature` (`id`, `event`, `sensor`, `celsius`) VALUES
(1, '2015-06-18 00:00:00', '288884820500006X', '1369'),
(2, '2015-06-17 02:25:06', '288884820500006X', '50'),
(3, '2015-06-17 02:25:11', '288884820500006X', '51'),
(4, '2015-06-17 02:25:16', '288884820500006X', '52'),
(5, '2015-06-17 02:25:21', '288884820500006X', '53'),
(6, '2015-06-17 02:25:33', '288884820500006X', '20');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
