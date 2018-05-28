-- phpMyAdmin SQL Dump
-- version 4.6.6deb4
-- https://www.phpmyadmin.net/
--
-- Client :  localhost:3306
-- Généré le :  Lun 28 Mai 2018 à 14:37
-- Version du serveur :  10.1.23-MariaDB-9+deb9u1
-- Version de PHP :  7.0.27-0+deb9u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `ruche`
--

-- --------------------------------------------------------

--
-- Structure de la table `abeilles`
--

CREATE TABLE `abeilles` (
  `idabeilles` int(11) NOT NULL,
  `beeinside` tinyint(4) DEFAULT NULL,
  `beeoutside` varchar(45) DEFAULT NULL,
  `date` datetime NOT NULL,
  `ruches_idRuches` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Doublure de structure pour la vue `Alertes_1hour`
-- (Voir ci-dessous la vue réelle)
--
CREATE TABLE `Alertes_1hour` (
`tempval` float
,`date` datetime
,`poidsval` float
);

-- --------------------------------------------------------

--
-- Structure de la table `apiculteurs`
--

CREATE TABLE `apiculteurs` (
  `idapiculteurs` int(11) NOT NULL,
  `login` varchar(45) NOT NULL,
  `mdp` varchar(45) NOT NULL,
  `nom` varchar(45) DEFAULT NULL,
  `prenom` varchar(45) DEFAULT NULL,
  `telephone` varchar(10) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL,
  `droits` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Contenu de la table `apiculteurs`
--

INSERT INTO `apiculteurs` (`idapiculteurs`, `login`, `mdp`, `nom`, `prenom`, `telephone`, `email`, `droits`) VALUES
(1, 'kchevalier', 'toto', 'Chevalier', 'Kevin', '0658280206', 'kevin.antoine.chevalier@gmail.com', 0),
(2, 'toto', 'toto', 'Toshi', 'Algin', '0600000000', 'toshi.algin@gmail.com', 1),
(3, 'aa', 'aa', 'aaa', 'aaaa', '01', 'a', 0);

-- --------------------------------------------------------

--
-- Structure de la table `mesures`
--

CREATE TABLE `mesures` (
  `idonnees` int(11) NOT NULL,
  `eclairementval` float NOT NULL,
  `pressionval` float NOT NULL,
  `tempval` float NOT NULL,
  `poidsval` float NOT NULL,
  `humidval` float NOT NULL,
  `tempfahr` float NOT NULL,
  `tension` float NOT NULL,
  `courant` float NOT NULL,
  `date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `ruches_idRuches` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Contenu de la table `mesures`
--

INSERT INTO `mesures` (`idonnees`, `eclairementval`, `pressionval`, `tempval`, `poidsval`, `humidval`, `tempfahr`, `tension`, `courant`, `date`, `ruches_idRuches`) VALUES
(1, 20, 1020, 21, 45, 0, 0, 0, 0, '2018-03-30 08:30:00', 1),
(4, 0, 0, 41, 45, 0, 0, 0, 0, '2018-04-03 09:14:24', 1),
(5, 0, 0, 41, 45, 0, 0, 0, 0, '2018-04-03 09:15:46', 1),
(6, 0, 0, 41, 45, 0, 0, 0, 0, '2018-04-03 09:19:33', 1),
(7, 0, 0, 41, 45, 0, 0, 0, 0, '2018-04-03 09:22:24', 1),
(8, 0, 0, 41, 45, 0, 0, 0, 0, '2018-04-03 09:37:01', 1),
(9, 0, 0, 51, 45, 0, 0, 0, 0, '2018-04-03 09:45:56', 1),
(10, 0, 0, 18, 39, 0, 0, 0, 0, '2018-04-03 12:05:37', 1),
(11, 0, 0, 51, 0, 0, 0, 0, 0, '2018-04-06 10:36:11', 1),
(12, 300, 1000, 25, 40, 38, 77, 0, 0, '2018-04-19 15:30:05', 1),
(13, 0, 1022.79, 35.08, 0, 27.71, 95.14, 0, 0, '2018-04-19 16:15:37', 1),
(14, 0, 1022.35, 33.82, 0, 28.08, 92.88, 0, 0, '2018-04-19 16:21:16', 1),
(15, 0, 1021.8, 24.94, 0, 49.92, 76.93, 0, 0, '2018-04-20 08:46:14', 1),
(16, 1250, 1016.8, 18.5, 40, 25, 80, 0, 0, '2018-04-20 08:53:48', 1),
(17, 0, 1022.01, 26.18, 0, 48.25, 79.12, 0, 0, '2018-04-20 08:55:56', 1),
(18, 0, 1022.14, 26.8, 0, 49.17, 80.24, 0, 0, '2018-04-20 09:02:25', 1),
(19, 300, 1000, 25, 40, 38, 77, 0, 0, '2018-04-20 09:09:01', 1),
(20, 200, 1000, 20, 45, 30, 90, 0, 0, '2018-04-20 09:18:26', 1),
(21, 0, 1021.95, 26.43, 0, 47.86, 79.57, 0, 0, '2018-04-20 09:26:37', 1),
(22, 0, 1023.24, 31.78, 0, 79.89, 89.2, 0, 0, '2018-04-20 09:29:40', 1),
(23, 0, 0, 8.04, 0, 0, 46.47, 0, 0, '2018-04-20 10:31:35', 1),
(24, 200, 1000, 20, 45, 30, 90, 0, 0, '2018-04-20 11:09:32', 1),
(25, 300, 1000, 25, 40, 38, 77, 0, 0, '2018-04-20 11:17:00', 1),
(26, 0, 1018.81, 28.79, 0, 33.74, 83.82, 0, 0, '2018-04-23 15:55:50', 1),
(27, 0, 1018.9, 29.39, 0, 32.24, 84.92, 0, 0, '2018-04-23 16:00:09', 1),
(28, 0, 1019, 25.25, 0, 39.6, 77.47, 0, 0, '2018-04-24 09:16:08', 1),
(29, 0, 1019.08, 25.65, 0, 38.32, 78.17, 0, 0, '2018-04-24 09:17:07', 1),
(30, 0, 1019.04, 25.68, 0, 38.1, 78.24, 0, 0, '2018-04-24 09:18:23', 1),
(31, 320, 0, 0, 0, 0, 0, 0, 0, '2018-04-24 09:31:34', 1),
(32, 0, 1016.93, 22.94, 0, 49.46, 73.31, 0, 0, '2018-05-16 09:36:22', 1),
(33, 0, 1016.81, 22.94, 0, 49.83, 73.29, 0, 0, '2018-05-16 09:36:44', 1),
(34, 0, 1015.92, 27.24, 0, 51.48, 81.03, 0, 0, '2018-05-24 13:36:00', 1),
(35, 0, 1015.87, 27.29, 0, 50.64, 81.12, 0, 0, '2018-05-24 13:37:16', 1),
(36, 0, 1015.84, 27.38, 0, 49.87, 81.28, 0, 0, '2018-05-24 13:39:39', 1),
(37, 9.55, 1014.66, 26.05, 0, 60.47, 78.89, 0, 0, '2018-05-28 10:10:25', 1),
(38, 9.55, 1014.68, 26.07, 0, 60.55, 78.93, 0, 0, '2018-05-28 10:11:17', 1),
(39, 9.55, 1014.9, 26.48, 0, 57.1, 79.66, 0, 0, '2018-05-28 10:42:26', 1),
(40, 9.546, 1014.75, 26.68, 0, 56.01, 80.01, 0, 0, '2018-05-28 10:57:21', 1),
(41, 9.546, 1014.75, 26.88, 0, 55.31, 80.38, 0, 0, '2018-05-28 11:10:01', 1),
(42, 9.546, 1014.74, 26.97, 0, 54.34, 80.55, 0, 0, '2018-05-28 11:20:01', 1);

-- --------------------------------------------------------

--
-- Structure de la table `ruches`
--

CREATE TABLE `ruches` (
  `idRuches` int(11) NOT NULL,
  `nomRuche` varchar(50) NOT NULL,
  `seuilPoids` float DEFAULT NULL,
  `seuilTempBasse` float DEFAULT NULL,
  `seuilTempHaute` float DEFAULT NULL,
  `longitude` float DEFAULT NULL,
  `lattitude` float DEFAULT NULL,
  `altitude` float DEFAULT NULL,
  `ville` varchar(50) NOT NULL,
  `apiculteurs_idapiculteurs` int(11) NOT NULL,
  `descriptionRuche` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Contenu de la table `ruches`
--

INSERT INTO `ruches` (`idRuches`, `nomRuche`, `seuilPoids`, `seuilTempBasse`, `seuilTempHaute`, `longitude`, `lattitude`, `altitude`, `ville`, `apiculteurs_idapiculteurs`, `descriptionRuche`) VALUES
(1, '', 40, -5, 40, 0.204433, 47.9957, 40, 'Le Mans', 1, 'Ruche de test');

-- --------------------------------------------------------

--
-- Structure de la vue `Alertes_1hour`
--
DROP TABLE IF EXISTS `Alertes_1hour`;

CREATE ALGORITHM=UNDEFINED DEFINER=`ruche`@`%` SQL SECURITY DEFINER VIEW `Alertes_1hour`  AS  select `mesures`.`tempval` AS `tempval`,`mesures`.`date` AS `date`,`mesures`.`poidsval` AS `poidsval` from (`mesures` join `ruches`) where (((`mesures`.`tempval` > `ruches`.`seuilTempHaute`) or (`mesures`.`poidsval` < `ruches`.`seuilPoids`)) and (`mesures`.`date` >= (now() - interval 1 hour))) ;

--
-- Index pour les tables exportées
--

--
-- Index pour la table `abeilles`
--
ALTER TABLE `abeilles`
  ADD PRIMARY KEY (`idabeilles`),
  ADD KEY `fk_abeilles_ruches1_idx` (`ruches_idRuches`);

--
-- Index pour la table `apiculteurs`
--
ALTER TABLE `apiculteurs`
  ADD PRIMARY KEY (`idapiculteurs`);

--
-- Index pour la table `mesures`
--
ALTER TABLE `mesures`
  ADD PRIMARY KEY (`idonnees`),
  ADD KEY `fk_donneesval_ruches1_idx` (`ruches_idRuches`);

--
-- Index pour la table `ruches`
--
ALTER TABLE `ruches`
  ADD PRIMARY KEY (`idRuches`),
  ADD KEY `fk_ruches_apiculteurs_idx` (`apiculteurs_idapiculteurs`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `apiculteurs`
--
ALTER TABLE `apiculteurs`
  MODIFY `idapiculteurs` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT pour la table `mesures`
--
ALTER TABLE `mesures`
  MODIFY `idonnees` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=43;
--
-- AUTO_INCREMENT pour la table `ruches`
--
ALTER TABLE `ruches`
  MODIFY `idRuches` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `abeilles`
--
ALTER TABLE `abeilles`
  ADD CONSTRAINT `fk_abeilles_ruches1` FOREIGN KEY (`ruches_idRuches`) REFERENCES `ruches` (`idRuches`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Contraintes pour la table `mesures`
--
ALTER TABLE `mesures`
  ADD CONSTRAINT `fk_donneesval_ruches1` FOREIGN KEY (`ruches_idRuches`) REFERENCES `ruches` (`idRuches`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Contraintes pour la table `ruches`
--
ALTER TABLE `ruches`
  ADD CONSTRAINT `fk_ruches_apiculteurs` FOREIGN KEY (`apiculteurs_idapiculteurs`) REFERENCES `apiculteurs` (`idapiculteurs`) ON DELETE NO ACTION ON UPDATE NO ACTION;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
