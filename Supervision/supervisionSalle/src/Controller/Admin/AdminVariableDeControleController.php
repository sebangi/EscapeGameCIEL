<?php

namespace App\Controller\Admin;

use App\Entity\VariableDeControle;
use App\Form\VariableDeControleType;
use App\Repository\VariableDeControleRepository;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

#[Route('/admin/controle')]
class AdminVariableDeControleController extends AbstractController
{
    #[Route('/', name: 'app_variable_de_controle_index', methods: ['GET'])]
    public function index(VariableDeControleRepository $variableDeControleRepository): Response
    {
        return $this->render('variable_de_controle/index.html.twig', [
            'variable_de_controles' => $variableDeControleRepository->findAll(),
        ]);
    }

    #[Route('/new', name: 'app_variable_de_controle_new', methods: ['GET', 'POST'])]
    public function new(Request $request, VariableDeControleRepository $variableDeControleRepository): Response
    {
        $variableDeControle = new VariableDeControle();
        $form = $this->createForm(VariableDeControleType::class, $variableDeControle);
        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $variableDeControleRepository->save($variableDeControle, true);

            return $this->redirectToRoute('app_variable_de_controle_index', [], Response::HTTP_SEE_OTHER);
        }

        return $this->renderForm('variable_de_controle/new.html.twig', [
            'variable_de_controle' => $variableDeControle,
            'form' => $form,
        ]);
    }

    #[Route('/{id}', name: 'app_variable_de_controle_show', methods: ['GET'])]
    public function show(VariableDeControle $variableDeControle): Response
    {
        return $this->render('variable_de_controle/show.html.twig', [
            'variable_de_controle' => $variableDeControle,
        ]);
    }

    #[Route('/{id}/edit', name: 'app_variable_de_controle_edit', methods: ['GET', 'POST'])]
    public function edit(Request $request, VariableDeControle $variableDeControle, VariableDeControleRepository $variableDeControleRepository): Response
    {
        $form = $this->createForm(VariableDeControleType::class, $variableDeControle);
        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $variableDeControleRepository->save($variableDeControle, true);

            return $this->redirectToRoute('app_variable_de_controle_index', [], Response::HTTP_SEE_OTHER);
        }

        return $this->renderForm('variable_de_controle/edit.html.twig', [
            'variable_de_controle' => $variableDeControle,
            'form' => $form,
        ]);
    }

    #[Route('/{id}', name: 'app_variable_de_controle_delete', methods: ['POST'])]
    public function delete(Request $request, VariableDeControle $variableDeControle, VariableDeControleRepository $variableDeControleRepository): Response
    {
        if ($this->isCsrfTokenValid('delete'.$variableDeControle->getId(), $request->request->get('_token'))) {
            $variableDeControleRepository->remove($variableDeControle, true);
        }

        return $this->redirectToRoute('app_variable_de_controle_index', [], Response::HTTP_SEE_OTHER);
    }
}
