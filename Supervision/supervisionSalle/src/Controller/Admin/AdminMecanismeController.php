<?php

namespace App\Controller\Admin;

use App\Entity\Mecanisme;
use App\Entity\Salle;
use App\Form\MecanismeType;
use App\Repository\MecanismeRepository;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

#[Route('/admin/mecanisme')]
class AdminMecanismeController extends AbstractController
{
    #[Route('/', name: 'app_mecanisme_index', methods: ['GET'])]
    public function index(MecanismeRepository $mecanismeRepository): Response
    {
        return $this->render('admin/mecanisme/index.html.twig', [
            'mecanismes' => $mecanismeRepository->findAll(),
        ]);
    }

    #[Route('/{id}/newmecanisme', name: 'app_mecanisme_new', methods: ['GET', 'POST'])]
    public function new(Request $request, Salle $salle, MecanismeRepository $mecanismeRepository): Response
    {
        $mecanisme = new Mecanisme();
        $mecanisme->setSalle($salle);
        $form = $this->createForm(MecanismeType::class, $mecanisme);
        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $mecanismeRepository->save($mecanisme, true);
            $this->addFlash('success', 'Mécanisme ajouté avec succès.');
            
            return $this->render('admin/mecanisme/show.html.twig', [
                'mecanisme' => $mecanisme,
            ]);
        }

        return $this->renderForm('admin/mecanisme/new.html.twig', [
            'mecanisme' => $mecanisme,
                'salle' => $mecanisme->getSalle(),
            'form' => $form,
        ]);
    }

    #[Route('/{id}', name: 'app_mecanisme_show', methods: ['GET'])]
    public function show(Mecanisme $mecanisme): Response
    {
        return $this->render('admin/mecanisme/show.html.twig', [
            'mecanisme' => $mecanisme,
        ]);
    }

    #[Route('/{id}/edit', name: 'app_mecanisme_edit', methods: ['GET', 'POST'])]
    public function edit(Request $request, Mecanisme $mecanisme, MecanismeRepository $mecanismeRepository): Response
    {
        $form = $this->createForm(MecanismeType::class, $mecanisme);
        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $mecanismeRepository->save($mecanisme, true);
            $this->addFlash('success', 'Mécanisme modifié avec succès.');
            
            return $this->render('admin/mecanisme/show.html.twig', [
                'mecanisme' => $mecanisme,
            ]);
        }

        return $this->renderForm('admin/mecanisme/edit.html.twig', [
            'mecanisme' => $mecanisme,
            'form' => $form,
        ]);
    }

    #[Route('/{id}', name: 'app_mecanisme_delete', methods: ['POST'])]
    public function delete(Request $request, Mecanisme $mecanisme, MecanismeRepository $mecanismeRepository): Response
    {
        $idSalle = $mecanisme->getSalle()->getId();
                
        if ($this->isCsrfTokenValid('delete'.$mecanisme->getId(), $request->request->get('_token'))) {
            $mecanismeRepository->remove($mecanisme, true);
            $this->addFlash('success', 'Mécanisme supprimé avec succès.');
        }

        return $this->redirectToRoute('app_admin_salle_show', ['id' => $idSalle], Response::HTTP_SEE_OTHER);
    }
    
    #[Route('/{id}/delete', name: 'app_mecanisme_delete_verification', methods: ['GET', 'POST'])]
    public function deleteVerification(Request $request, Mecanisme $mecanisme): Response
    {
       return $this->render('admin/mecanisme/delete.html.twig', [
            'mecanisme' => $mecanisme,
        ]);      
       
    }
}
