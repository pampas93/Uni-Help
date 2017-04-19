//
//  StudentHomeViewController.swift
//  Unihelp
//
//  Created by Abhijit Srikanth on 4/17/17.
//  Copyright © 2017 SuProject. All rights reserved.
//

import UIKit

class StudentHomeViewController: UIViewController {


    @IBOutlet weak var menuButton: UIBarButtonItem!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        if self.revealViewController() != nil {
            menuButton.target = self.revealViewController()
            menuButton.action = #selector(SWRevealViewController.revealToggle(_:))
            self.view.addGestureRecognizer(self.revealViewController().panGestureRecognizer())
        }
        

        // Do any additional setup after loading the view.
    }

    
    
}