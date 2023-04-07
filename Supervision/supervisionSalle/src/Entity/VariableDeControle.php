<?php

namespace App\Entity;

use App\Repository\VariableDeControleRepository;
use Doctrine\DBAL\Types\Types;
use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity(repositoryClass: VariableDeControleRepository::class)]
class VariableDeControle
{
    #[ORM\Id]
    #[ORM\GeneratedValue]
    #[ORM\Column]
    private ?int $id = null;

    #[ORM\Column(length: 255)]
    private ?string $nom = null;

    #[ORM\Column]
    private ?int $numero = null;

    #[ORM\Column(type: Types::SMALLINT, nullable: true)]
    private ?int $valeur = null;

    #[ORM\Column]
    private ?bool $controle = null;

    #[ORM\Column(type: Types::SMALLINT)]
    private ?int $valeurControle = null;

    #[ORM\Column(type: Types::DATETIME_MUTABLE, nullable: true)]
    private ?\DateTimeInterface $valeurHorodatage = null;

    #[ORM\Column(length: 255)]
    private ?string $type = null;

    #[ORM\ManyToOne(inversedBy: 'variables')]
    #[ORM\JoinColumn(nullable: false)]
    private ?Mecanisme $mecanisme = null;

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getNom(): ?string
    {
        return $this->nom;
    }

    public function setNom(string $nom): self
    {
        $this->nom = $nom;

        return $this;
    }

    public function getNumero(): ?int
    {
        return $this->numero;
    }

    public function setNumero(int $numero): self
    {
        $this->numero = $numero;

        return $this;
    }

    public function getValeur(): ?int
    {
        return $this->valeur;
    }

    public function setValeur(?int $valeur): self
    {
        $this->valeur = $valeur;

        return $this;
    }

    public function isControle(): ?bool
    {
        return $this->controle;
    }

    public function setControle(bool $controle): self
    {
        $this->controle = $controle;

        return $this;
    }

    public function getValeurControle(): ?int
    {
        return $this->valeurControle;
    }

    public function setValeurControle(int $valeurControle): self
    {
        $this->valeurControle = $valeurControle;

        return $this;
    }

    public function getValeurHorodatage(): ?\DateTimeInterface
    {
        return $this->valeurHorodatage;
    }

    public function setValeurHorodatage(?\DateTimeInterface $valeurHorodatage): self
    {
        $this->valeurHorodatage = $valeurHorodatage;

        return $this;
    }

    public function getType(): ?string
    {
        return $this->type;
    }

    public function setType(string $type): self
    {
        $this->type = $type;

        return $this;
    }

    public function getMecanisme(): ?Mecanisme
    {
        return $this->mecanisme;
    }

    public function setMecanisme(?Mecanisme $mecanisme): self
    {
        $this->mecanisme = $mecanisme;

        return $this;
    }
}
