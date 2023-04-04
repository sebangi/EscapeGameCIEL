<?php

namespace App\Form;

use App\Entity\Utilisateur;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;
use Symfony\Component\Form\Extension\Core\Type\PasswordType;
use Symfony\Component\Form\Extension\Core\Type\RepeatedType;

class UtilisateurType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder
            ->add('username')
            ;            

        if ($options['nouveau'] == true) {
            $builder
                ->add('password', RepeatedType::class, [
                        'type' => PasswordType::class,
                        'first_options' => array('label' => 'Mot de passe'),
                        'second_options' => array('label' => 'Répétez le mot de passe'),
                        'mapped' => false,
                        'invalid_message' => 'Les mots de passe ne sont pas identiques. Saisissez-les à nouveau !',
            ]);
        }
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'data_class' => Utilisateur::class,
            'nouveau' => false,
        ]);
    }
}
