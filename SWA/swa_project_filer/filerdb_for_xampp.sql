-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Erstellungszeit: 11. Jun 2023 um 22:37
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
(251);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tdirectory`
--

CREATE TABLE `tdirectory` (
  `directory_id` int(11) NOT NULL,
  `group_id` int(11) NOT NULL,
  `user_id` bigint(20) NOT NULL,
  `name` varchar(255) NOT NULL,
  `subdir_id` int(11) DEFAULT NULL,
  `created_at` datetime NOT NULL DEFAULT current_timestamp(),
  `updated_at` datetime NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `tdirectory`
--

INSERT INTO `tdirectory` (`directory_id`, `group_id`, `user_id`, `name`, `subdir_id`, `created_at`, `updated_at`) VALUES
(1, 1, 1, 'Directory_1', NULL, '2023-06-11 12:11:41', '2023-06-11 22:36:40'),
(2, 1, 1, 'Directory_2', 1, '2023-06-11 12:11:41', '2023-06-11 13:35:03'),
(3, 2, 2, 'Directory_1', NULL, '2023-06-11 12:11:41', '2023-06-11 22:36:42');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tfiles`
--

CREATE TABLE `tfiles` (
  `file_id` int(11) NOT NULL,
  `directory_id` int(11) NOT NULL,
  `file_size` int(11) NOT NULL,
  `store_path` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Daten für Tabelle `tfiles`
--

INSERT INTO `tfiles` (`file_id`, `directory_id`, `file_size`, `store_path`) VALUES
(3, 1, 1000, '/path/to/file1.txt'),
(4, 2, 1000, '/path/to/file2.txt');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tgroupmembers`
--

CREATE TABLE `tgroupmembers` (
  `member_id` int(11) NOT NULL,
  `group_id` int(11) NOT NULL,
  `permissions` enum('r','rw') NOT NULL DEFAULT 'r',
  `user_id` bigint(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `tgroupmembers`
--

INSERT INTO `tgroupmembers` (`member_id`, `group_id`, `permissions`, `user_id`) VALUES
(1, 1, 'r', 1),
(2, 2, 'rw', 2),
(3, 2, 'rw', 3);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `tgroups`
--

CREATE TABLE `tgroups` (
  `group_id` int(11) NOT NULL,
  `founder_id` bigint(20) NOT NULL,
  `created_at` datetime NOT NULL DEFAULT current_timestamp(),
  `updated_at` datetime NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Daten für Tabelle `tgroups`
--

INSERT INTO `tgroups` (`group_id`, `founder_id`, `created_at`, `updated_at`) VALUES
(1, 1, '2023-06-11 12:11:10', '2023-06-11 12:11:10'),
(2, 2, '2023-06-11 12:11:10', '2023-06-11 12:11:10'),
(3, 3, '2023-06-11 12:11:10', '2023-06-11 12:11:10');

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
(1, '1990-01-29', 'hansmueller@web.com', 'Hans', 'Mueller', '$2a$12$gSSObvjzyuYSgqDrnk3YSeyOUbkXeAo2FWPrAQq9xNHLYZ0Nj/duK', 'user'),
(2, '1999-04-11', 'mati@web.com', 'Tadeus', 'Freitag', '$2a$12$gSSObvjzyuYSgqDrnk3YSeyOUbkXeAo2FWPrAQq9xNHLYZ0Nj/duK', 'admin'),
(3, '2000-07-20', 'admin@web.com', 'John', 'Doe', '$2a$12$gSSObvjzyuYSgqDrnk3YSeyOUbkXeAo2FWPrAQq9xNHLYZ0Nj/duK', 'admin');

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
  ADD KEY `group_id` (`group_id`),
  ADD KEY `user_id` (`user_id`),
  ADD KEY `subdir_id` (`subdir_id`);

--
-- Indizes für die Tabelle `tfiles`
--
ALTER TABLE `tfiles`
  ADD PRIMARY KEY (`file_id`),
  ADD KEY `directory_id` (`directory_id`);

--
-- Indizes für die Tabelle `tgroupmembers`
--
ALTER TABLE `tgroupmembers`
  ADD PRIMARY KEY (`member_id`),
  ADD KEY `group_id` (`group_id`),
  ADD KEY `user_id` (`user_id`);

--
-- Indizes für die Tabelle `tgroups`
--
ALTER TABLE `tgroups`
  ADD PRIMARY KEY (`group_id`),
  ADD KEY `founder_id` (`founder_id`);

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
  MODIFY `directory_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT für Tabelle `tfiles`
--
ALTER TABLE `tfiles`
  MODIFY `file_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT für Tabelle `tgroupmembers`
--
ALTER TABLE `tgroupmembers`
  MODIFY `member_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT für Tabelle `tgroups`
--
ALTER TABLE `tgroups`
  MODIFY `group_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT für Tabelle `tusers`
--
ALTER TABLE `tusers`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

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
  ADD CONSTRAINT `tdirectory_group_id_foreign` FOREIGN KEY (`group_id`) REFERENCES `tgroupmembers` (`group_id`),
  ADD CONSTRAINT `tdirectory_subdir_id_foreign` FOREIGN KEY (`subdir_id`) REFERENCES `tdirectory` (`directory_id`),
  ADD CONSTRAINT `tdirectory_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `tusers` (`id`);

--
-- Constraints der Tabelle `tfiles`
--
ALTER TABLE `tfiles`
  ADD CONSTRAINT `tfiles_directory_id_foreign` FOREIGN KEY (`directory_id`) REFERENCES `tdirectory` (`directory_id`);

--
-- Constraints der Tabelle `tgroupmembers`
--
ALTER TABLE `tgroupmembers`
  ADD CONSTRAINT `tgroupmembers_group_id_foreign` FOREIGN KEY (`group_id`) REFERENCES `tgroups` (`group_id`),
  ADD CONSTRAINT `tgroupmembers_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `tusers` (`id`);

--
-- Constraints der Tabelle `tgroups`
--
ALTER TABLE `tgroups`
  ADD CONSTRAINT `tgroups_founder_id_foreign` FOREIGN KEY (`founder_id`) REFERENCES `tusers` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
