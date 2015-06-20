-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generato il: Giu 20, 2015 alle 19:51
-- Versione del server: 5.5.40
-- Versione PHP: 5.3.10-1ubuntu3.15

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `test`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `setpoint`
--

CREATE TABLE IF NOT EXISTS `setpoint` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'unique ID',
  `event` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Event Date and Time',
  `analog1` varchar(30) COLLATE utf32_unicode_ci NOT NULL COMMENT 'Unique ID of thevalueset',
  `analog2` varchar(30) COLLATE utf32_unicode_ci NOT NULL COMMENT 'Measured Temperature in units',
  `analog3` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `analog4` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `analog5` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
  `analog6` varchar(30) COLLATE utf32_unicode_ci NOT NULL,
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf32 COLLATE=utf32_unicode_ci AUTO_INCREMENT=7 ;

--
-- Dump dei dati per la tabella `setpoint`
--

INSERT INTO `setpoint` (`id`, `event`, `analog1`, `analog2`, `analog3`, `analog4`, `analog5`, `analog6`, `digital0`, `digital1`, `digital2`, `digital3`, `digital4`, `pwm0`, `pwm1`, `pwm2`) VALUES
(1, '2015-06-18 00:00:00', '475', '427', '419', '420', '426', '452', '10', '11', '12', '13', '14', '100', '101', '102');

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf32 COLLATE=utf32_unicode_ci AUTO_INCREMENT=7 ;

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
