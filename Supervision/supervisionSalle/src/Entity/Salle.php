<?php

namespace App\Entity;

use App\Repository\SalleRepository;
use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;
use Doctrine\DBAL\Types\Types;
use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity(repositoryClass: SalleRepository::class)]
class Salle
{
    #[ORM\Id]
    #[ORM\GeneratedValue]
    #[ORM\Column]
    private ?int $id = null;

    #[ORM\Column(unique:true)]
    private ?int $numero = null;

    #[ORM\Column(length: 255)]
    private ?string $nom = null;

    #[ORM\Column(type: Types::TEXT)]
    private ?string $description = null;

    #[ORM\OneToMany(mappedBy: 'salle', targetEntity: Mecanisme::class, orphanRemoval: true)]
    private Collection $mecanismes;

    public function __construct()
    {
        $this->mecanismes = new ArrayCollection();
    }

    public function getId(): ?int
    {
        return $this->id;
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

    public function getNom(): ?string
    {
        return $this->nom;
    }

    public function setNom(string $nom): self
    {
        $this->nom = $nom;

        return $this;
    }

    public function getDescription(): ?string
    {
        return $this->description;
    }

    public function setDescription(string $description): self
    {
        $this->description = $description;

        return $this;
    }

    /**
     * @return Collection<int, Mecanisme>
     */
    public function getMecanismes(): Collection
    {
        return $this->mecanismes;
    }

    public function addMecanisme(Mecanisme $mecanisme): self
    {
        if (!$this->mecanismes->contains($mecanisme)) {
            $this->mecanismes->add($mecanisme);
            $mecanisme->setSalle($this);
        }

        return $this;
    }

    public function removeMecanisme(Mecanisme $mecanisme): self
    {
        if ($this->mecanismes->removeElement($mecanisme)) {
            // set the owning side to null (unless already changed)
            if ($mecanisme->getSalle() === $this) {
                $mecanisme->setSalle(null);
            }
        }

        return $this;
    }
}
