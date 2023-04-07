<?php

declare(strict_types=1);

namespace DoctrineMigrations;

use Doctrine\DBAL\Schema\Schema;
use Doctrine\Migrations\AbstractMigration;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
final class Version20230407113552 extends AbstractMigration
{
    public function getDescription(): string
    {
        return '';
    }

    public function up(Schema $schema): void
    {
        // this up() migration is auto-generated, please modify it to your needs
        $this->addSql('CREATE TABLE mecanisme (id INT AUTO_INCREMENT NOT NULL, salle_id INT NOT NULL, nom VARCHAR(255) NOT NULL, numero INT NOT NULL, description LONGTEXT DEFAULT NULL, INDEX IDX_71C87194DC304035 (salle_id), PRIMARY KEY(id)) DEFAULT CHARACTER SET utf8mb4 COLLATE `utf8mb4_unicode_ci` ENGINE = InnoDB');
        $this->addSql('CREATE TABLE variable_de_controle (id INT AUTO_INCREMENT NOT NULL, mecanisme_id INT NOT NULL, nom VARCHAR(255) NOT NULL, numero INT NOT NULL, valeur SMALLINT DEFAULT NULL, controle TINYINT(1) NOT NULL, valeur_controle SMALLINT NOT NULL, valeur_horodatage DATETIME DEFAULT NULL, type VARCHAR(255) NOT NULL, INDEX IDX_B10C73623FC0D758 (mecanisme_id), PRIMARY KEY(id)) DEFAULT CHARACTER SET utf8mb4 COLLATE `utf8mb4_unicode_ci` ENGINE = InnoDB');
        $this->addSql('ALTER TABLE mecanisme ADD CONSTRAINT FK_71C87194DC304035 FOREIGN KEY (salle_id) REFERENCES salle (id)');
        $this->addSql('ALTER TABLE variable_de_controle ADD CONSTRAINT FK_B10C73623FC0D758 FOREIGN KEY (mecanisme_id) REFERENCES mecanisme (id)');
    }

    public function down(Schema $schema): void
    {
        // this down() migration is auto-generated, please modify it to your needs
        $this->addSql('ALTER TABLE mecanisme DROP FOREIGN KEY FK_71C87194DC304035');
        $this->addSql('ALTER TABLE variable_de_controle DROP FOREIGN KEY FK_B10C73623FC0D758');
        $this->addSql('DROP TABLE mecanisme');
        $this->addSql('DROP TABLE variable_de_controle');
    }
}
