<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

class MainController extends AbstractController
{
    #[Route('/', name: 'app_home')]
    public function home(): Response
    {
        $message = "Ca marche !";
        
        return $this->render('main/home.html.twig', [
            'message' => $message,
        ]);
    }
    
    #[Route('/supervision', name: 'app_supervision_home')]
    public function supervision(): Response
    {
        return $this->render('supervision/supervisionHome.html.twig', []);
    }
    
     #[Route('/admin', name: 'app_admin_home')]
    public function admin(): Response
    {
        $message = "Ca marche !";
        
        return $this->render('admin/adminHome.html.twig', [
            'message' => $message,
        ]);
    }
}
