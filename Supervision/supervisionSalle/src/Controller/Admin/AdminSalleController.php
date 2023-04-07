<?php

namespace App\Controller\Admin;

use App\Entity\Salle;
use App\Form\SalleType;
use App\Repository\SalleRepository;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

#[Route('/admin/salle')]
class AdminSalleController extends AbstractController
{
    #[Route('/', name: 'app_admin_salle_index', methods: ['GET'])]
    public function index(SalleRepository $salleRepository): Response
    {
        return $this->render('admin/salle/index.html.twig', [
            'salles' => $salleRepository->findAll(),
        ]);
    }

    #[Route('/new', name: 'app_admin_salle_new', methods: ['GET', 'POST'])]
    public function new(Request $request, SalleRepository $salleRepository): Response
    {
        $salle = new Salle();
        $form = $this->createForm(SalleType::class, $salle);
        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $salleRepository->save($salle, true);
            $this->addFlash('success', 'Salle ajoutée avec succès.');

            return $this->render('admin/salle/show.html.twig', [
                'salle' => $salle,
            ]);
        }

        return $this->renderForm('admin/salle/new.html.twig', [
            'salle' => $salle,
            'form' => $form,
        ]);
    }

    #[Route('/{id}', name: 'app_admin_salle_show', methods: ['GET'])]
    public function show(Salle $salle): Response
    {
        return $this->render('admin/salle/show.html.twig', [
            'salle' => $salle,
        ]);
    }

    #[Route('/{id}/edit', name: 'app_admin_salle_edit', methods: ['GET', 'POST'])]
    public function edit(Request $request, Salle $salle, SalleRepository $salleRepository): Response
    {
        $form = $this->createForm(SalleType::class, $salle);
        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $salleRepository->save($salle, true);
            $this->addFlash('success', 'Salle modifiée avec succès.');

            return $this->render('admin/salle/show.html.twig', [
                'salle' => $salle,
            ]);
        }

        return $this->renderForm('admin/salle/edit.html.twig', [
            'salle' => $salle,
            'form' => $form,
        ]);
    }

    #[Route('/{id}', name: 'app_admin_salle_delete', methods: ["POST"])]
    public function delete(Request $request, Salle $salle, SalleRepository $salleRepository): Response
    {
        if ($this->isCsrfTokenValid('delete'.$salle->getId(), $request->request->get('_token'))) {
            $salleRepository->remove($salle, true);
            $this->addFlash('success', 'Salle supprimée avec succès.');
        }
        
        return $this->redirectToRoute('app_admin_salle_index', [], Response::HTTP_SEE_OTHER);
    }
}
