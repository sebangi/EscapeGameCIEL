<?php

namespace App\Controller\Admin;

use App\Entity\Mecanisme;
use App\Entity\Salle;
use App\Form\MecanismeType;
use App\Repository\MecanismeRepository;
use App\Repository\SalleRepository;
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
        return $this->render('mecanisme/index.html.twig', [
            'mecanismes' => $mecanismeRepository->findAll(),
        ]);
    }

    #[Route('/new', name: 'app_mecanisme_new', methods: ['GET', 'POST'])]
    public function new(Request $request, MecanismeRepository $mecanismeRepository, Salle $salle): Response
    {
        $mecanisme = new Mecanisme();
        $mecanisme->setSalle($salle);
        $form = $this->createForm(MecanismeType::class, $mecanisme);
        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $mecanismeRepository->save($mecanisme, true);

            return $this->render('mecanisme/show.html.twig', [
                'mecanisme' => $mecanisme,
            ]);
        }

        return $this->renderForm('mecanisme/new.html.twig', [
            'mecanisme' => $mecanisme,
            'form' => $form,
        ]);
    }

    #[Route('/{id}', name: 'app_mecanisme_show', methods: ['GET'])]
    public function show(Mecanisme $mecanisme): Response
    {
        return $this->render('mecanisme/show.html.twig', [
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

            return $this->render('mecanisme/show.html.twig', [
                'mecanisme' => $mecanisme,
            ]);
        }

        return $this->renderForm('mecanisme/edit.html.twig', [
            'mecanisme' => $mecanisme,
            'form' => $form,
        ]);
    }

    #[Route('/{id}', name: 'app_mecanisme_delete', methods: ['POST'])]
    public function delete(Request $request, Mecanisme $mecanisme, MecanismeRepository $mecanismeRepository): Response
    {
        if ($this->isCsrfTokenValid('delete'.$mecanisme->getId(), $request->request->get('_token'))) {
            $mecanismeRepository->remove($mecanisme, true);
        }

        return $this->redirectToRoute('app_mecanisme_index', [], Response::HTTP_SEE_OTHER);
    }
}
