-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Erstellungszeit: 13. Jun 2023 um 23:45
-- Server-Version: 10.4.22-MariaDB
-- PHP-Version: 8.1.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Datenbank: `filerdb`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `refreshtoken`
--

CREATE TABLE `refreshtoken` (
  `id` bigint(20) NOT NULL,
  `expiry_date` datetime NOT NULL,
  `token` varchar(255) NOT NULL,
  `user_id` bigint(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `refreshtoken`
--

INSERT INTO `refreshtoken` (`id`, `expiry_date`, `token`, `user_id`) VALUES
(653, '2023-06-14 21:43:14', '0be82a1e-a653-4c7f-8c58-33d068651488', 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `refreshtoken_seq`
--

CREATE TABLE `refreshtoken_seq` (
  `next_val` bigint(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `refreshtoken_seq`
--

INSERT INTO `refreshtoken_seq` (`next_val`) VALUES
(751);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tdirectory`
--

CREATE TABLE `tdirectory` (
  `directory_id` bigint(20) NOT NULL,
  `created_at` datetime NOT NULL,
  `name` varchar(255) NOT NULL,
  `updated_at` datetime NOT NULL,
  `group_id_group_id` bigint(20) DEFAULT NULL,
  `subdir_id_directory_id` bigint(20) DEFAULT NULL,
  `user_id_id` bigint(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `tdirectory`
--

INSERT INTO `tdirectory` (`directory_id`, `created_at`, `name`, `updated_at`, `group_id_group_id`, `subdir_id_directory_id`, `user_id_id`) VALUES
(1, '2023-06-13 11:54:35', 'SWA', '2023-06-13 11:54:35', NULL, 2, 1),
(2, '2023-06-13 12:18:49', 'Documents', '2023-06-13 12:18:49', 1, NULL, 1),
(3, '2023-06-13 12:35:27', 'Project1', '2023-06-13 12:35:27', NULL, 6, 1),
(4, '2023-06-13 12:35:41', 'test3', '2023-06-13 12:35:41', NULL, NULL, NULL),
(5, '2023-06-13 12:35:56', 'test4', '2023-06-13 12:35:56', NULL, NULL, NULL),
(6, '2023-06-13 12:36:09', 'MCI2', '2023-06-13 12:36:09', NULL, 2, 1),
(7, '2023-06-13 12:36:32', 'test6', '2023-06-13 12:36:32', NULL, NULL, NULL),
(13, '2023-06-13 21:31:55', 'Project2', '2023-06-13 21:31:55', NULL, 6, 1),
(15, '2023-06-13 21:39:27', 'VR', '2023-06-13 21:39:27', NULL, 2, 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tfiles`
--

CREATE TABLE `tfiles` (
  `file_id` bigint(20) NOT NULL,
  `filename` varchar(255) NOT NULL,
  `filesize` bigint(20) DEFAULT NULL,
  `storepath` varchar(255) DEFAULT NULL,
  `directory_id_directory_id` bigint(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `tfiles`
--

INSERT INTO `tfiles` (`file_id`, `filename`, `filesize`, `storepath`, `directory_id_directory_id`) VALUES
(1, 'test', 123, '/admin/', 2);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tgroupmembers`
--

CREATE TABLE `tgroupmembers` (
  `id` bigint(20) NOT NULL,
  `group_group_id` bigint(20) DEFAULT NULL,
  `user_id` bigint(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tgroups`
--

CREATE TABLE `tgroups` (
  `group_id` bigint(20) NOT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  `founder_id_id` bigint(20) DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `tgroups`
--

INSERT INTO `tgroups` (`group_id`, `created_at`, `updated_at`, `founder_id_id`, `name`) VALUES
(1, '2023-06-13 18:46:32', '2023-06-13 18:46:32', 1, 'MyGroup');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tusers`
--

CREATE TABLE `tusers` (
  `id` bigint(20) NOT NULL,
  `dob` date NOT NULL,
  `email` varchar(45) NOT NULL,
  `f_name` varchar(20) NOT NULL,
  `l_name` varchar(20) NOT NULL,
  `password` varchar(64) NOT NULL,
  `role` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `tusers`
--

INSERT INTO `tusers` (`id`, `dob`, `email`, `f_name`, `l_name`, `password`, `role`) VALUES
(1, '2000-07-20', 'admin@hs-esslingen.de', 'Nico', 'Epp', '$2a$10$4wONPAua0N.AnqjnseJrfeKngRJVOepoW0mQ8zBCPbLRH5ogChJ7S', 'admin');

--
-- Indizes der exportierten Tabellen
--

--
-- Indizes für die Tabelle `refreshtoken`
--
ALTER TABLE `refreshtoken`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `UK_or156wbneyk8noo4jstv55ii3` (`token`),
  ADD KEY `FKdksv5xmavjmu82u7iofpvsla2` (`user_id`);

--
-- Indizes für die Tabelle `tdirectory`
--
ALTER TABLE `tdirectory`
  ADD PRIMARY KEY (`directory_id`),
  ADD KEY `FKs5a3ifm4ownlqhh5p3unj6rdx` (`group_id_group_id`),
  ADD KEY `FK6bu147ehk8qciaoc2wgcug5g4` (`subdir_id_directory_id`),
  ADD KEY `FKagumhnbmjql4s2i82pmh7e9gd` (`user_id_id`);

--
-- Indizes für die Tabelle `tfiles`
--
ALTER TABLE `tfiles`
  ADD PRIMARY KEY (`file_id`),
  ADD KEY `FK86ugq0b84g6v7e4yo8wvn06nv` (`directory_id_directory_id`);

--
-- Indizes für die Tabelle `tgroupmembers`
--
ALTER TABLE `tgroupmembers`
  ADD PRIMARY KEY (`id`),
  ADD KEY `FKk430b0e5a8uoi24hehg9mylt` (`group_group_id`),
  ADD KEY `FKp0gvcmhdmcjxl1i0wf8ntk0xs` (`user_id`);

--
-- Indizes für die Tabelle `tgroups`
--
ALTER TABLE `tgroups`
  ADD PRIMARY KEY (`group_id`),
  ADD KEY `FKlf4f0t5i7r0f7kmtw4aejp4k` (`founder_id_id`);

--
-- Indizes für die Tabelle `tusers`
--
ALTER TABLE `tusers`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `UK_15glla4w97tl62s6fm48u13hs` (`email`);

--
-- AUTO_INCREMENT für exportierte Tabellen
--

--
-- AUTO_INCREMENT für Tabelle `tdirectory`
--
ALTER TABLE `tdirectory`
  MODIFY `directory_id` bigint(20) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT für Tabelle `tfiles`
--
ALTER TABLE `tfiles`
  MODIFY `file_id` bigint(20) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT für Tabelle `tgroupmembers`
--
ALTER TABLE `tgroupmembers`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT für Tabelle `tgroups`
--
ALTER TABLE `tgroups`
  MODIFY `group_id` bigint(20) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT für Tabelle `tusers`
--
ALTER TABLE `tusers`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- Constraints der exportierten Tabellen
--

--
-- Constraints der Tabelle `refreshtoken`
--
ALTER TABLE `refreshtoken`
  ADD CONSTRAINT `FKdksv5xmavjmu82u7iofpvsla2` FOREIGN KEY (`user_id`) REFERENCES `tusers` (`id`);

--
-- Constraints der Tabelle `tdirectory`
--
ALTER TABLE `tdirectory`
  ADD CONSTRAINT `FK6bu147ehk8qciaoc2wgcug5g4` FOREIGN KEY (`subdir_id_directory_id`) REFERENCES `tdirectory` (`directory_id`),
  ADD CONSTRAINT `FKagumhnbmjql4s2i82pmh7e9gd` FOREIGN KEY (`user_id_id`) REFERENCES `tusers` (`id`),
  ADD CONSTRAINT `FKs5a3ifm4ownlqhh5p3unj6rdx` FOREIGN KEY (`group_id_group_id`) REFERENCES `tgroups` (`group_id`);

--
-- Constraints der Tabelle `tfiles`
--
ALTER TABLE `tfiles`
  ADD CONSTRAINT `FK86ugq0b84g6v7e4yo8wvn06nv` FOREIGN KEY (`directory_id_directory_id`) REFERENCES `tdirectory` (`directory_id`);

--
-- Constraints der Tabelle `tgroupmembers`
--
ALTER TABLE `tgroupmembers`
  ADD CONSTRAINT `FKk430b0e5a8uoi24hehg9mylt` FOREIGN KEY (`group_group_id`) REFERENCES `tgroups` (`group_id`),
  ADD CONSTRAINT `FKp0gvcmhdmcjxl1i0wf8ntk0xs` FOREIGN KEY (`user_id`) REFERENCES `tusers` (`id`);

--
-- Constraints der Tabelle `tgroups`
--
ALTER TABLE `tgroups`
  ADD CONSTRAINT `FKlf4f0t5i7r0f7kmtw4aejp4k` FOREIGN KEY (`founder_id_id`) REFERENCES `tusers` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
