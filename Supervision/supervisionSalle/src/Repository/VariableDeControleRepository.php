<?php

namespace App\Repository;

use App\Entity\VariableDeControle;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;

/**
 * @extends ServiceEntityRepository<VariableDeControle>
 *
 * @method VariableDeControle|null find($id, $lockMode = null, $lockVersion = null)
 * @method VariableDeControle|null findOneBy(array $criteria, array $orderBy = null)
 * @method VariableDeControle[]    findAll()
 * @method VariableDeControle[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class VariableDeControleRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, VariableDeControle::class);
    }

    public function save(VariableDeControle $entity, bool $flush = false): void
    {
        $this->getEntityManager()->persist($entity);

        if ($flush) {
            $this->getEntityManager()->flush();
        }
    }

    public function remove(VariableDeControle $entity, bool $flush = false): void
    {
        $this->getEntityManager()->remove($entity);

        if ($flush) {
            $this->getEntityManager()->flush();
        }
    }

//    /**
//     * @return VariableDeControle[] Returns an array of VariableDeControle objects
//     */
//    public function findByExampleField($value): array
//    {
//        return $this->createQueryBuilder('v')
//            ->andWhere('v.exampleField = :val')
//            ->setParameter('val', $value)
//            ->orderBy('v.id', 'ASC')
//            ->setMaxResults(10)
//            ->getQuery()
//            ->getResult()
//        ;
//    }

//    public function findOneBySomeField($value): ?VariableDeControle
//    {
//        return $this->createQueryBuilder('v')
//            ->andWhere('v.exampleField = :val')
//            ->setParameter('val', $value)
//            ->getQuery()
//            ->getOneOrNullResult()
//        ;
//    }
}
