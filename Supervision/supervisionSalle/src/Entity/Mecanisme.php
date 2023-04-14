<?php

namespace App\Entity;

use App\Entity\Salle;
use App\Repository\MecanismeRepository;
use Symfony\Component\Validator\Constraints as Assert;
use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;
use Doctrine\DBAL\Types\Types;
use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity(repositoryClass: MecanismeRepository::class)]
class Mecanisme
{
    #[ORM\Id]
    #[ORM\GeneratedValue]
    #[ORM\Column]
    private ?int $id = null;

    #[ORM\Column(length: 255)]
    private ?string $nom = null;

    #[ORM\Column]
    private ?int $numero = null;

    #[ORM\Column(type: Types::TEXT, nullable: true)]
    private ?string $description = null;

    #[ORM\ManyToOne(inversedBy: 'mecanismes')]
    #[ORM\JoinColumn(nullable: false)]
    private ?Salle $salle = null;

    #[ORM\OneToMany(mappedBy: 'mecanisme', targetEntity: VariableDeControle::class, orphanRemoval: true)]
    private Collection $variables;

    #[ORM\Column(length: 255)]
    #[Assert\Ip]
    private ?string $ip = null;

    public function __construct()
    {
        $this->variables = new ArrayCollection();
        $this->ip = "0.0.0.0";
    }

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

    public function getDescription(): ?string
    {
        return $this->description;
    }

    public function setDescription(?string $description): self
    {
        $this->description = $description;

        return $this;
    }

    public function getSalle(): ?Salle
    {
        return $this->salle;
    }

    public function setSalle(?Salle $salle): self
    {
        $this->salle = $salle;
        
        return $this;
    }

    /**
     * @return Collection<int, VariableDeControle>
     */
    public function getVariables(): Collection
    {
        return $this->variables;
    }

    public function addVariable(VariableDeControle $variable): self
    {
        if (!$this->variables->contains($variable)) {
            $this->variables->add($variable);
            $variable->setMecanisme($this);
        }

        return $this;
    }

    public function removeVariable(VariableDeControle $variable): self
    {
        if ($this->variables->removeElement($variable)) {
            // set the owning side to null (unless already changed)
            if ($variable->getMecanisme() === $this) {
                $variable->setMecanisme(null);
            }
        }

        return $this;
    }

    public function getIp(): ?string
    {
        return $this->ip;
    }

    public function setIp(string $ip): self
    {
        $this->ip = $ip;

        return $this;
    }
}
