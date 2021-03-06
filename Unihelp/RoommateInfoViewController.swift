//
//  RoommateInfoViewController.swift
//  Unihelp
//
//  Created by Abhijit Srikanth on 4/24/17.
//  Copyright © 2017 SuProject. All rights reserved.
//

import UIKit
import Firebase

class RoommateInfoViewController: UIViewController {
    
    var user: FIRUser!
    var ref: FIRDatabaseReference!
    let userID : String = (FIRAuth.auth()?.currentUser?.uid)!
    
    var student_uid : String = ""
    
    @IBOutlet weak var name: UILabel!
    @IBOutlet weak var country: UILabel!
    @IBOutlet weak var city: UILabel!
    @IBOutlet weak var mailID: UILabel!
    @IBOutlet weak var phone: UILabel!
    @IBOutlet weak var drink: UILabel!
    @IBOutlet weak var food: UILabel!
    @IBOutlet weak var smoke: UILabel!
    @IBOutlet weak var room: UILabel!
    @IBOutlet weak var aboutme: UILabel!
    @IBOutlet weak var university: UILabel!
    
    @IBOutlet weak var imageDP: UIImageView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        user = FIRAuth.auth()?.currentUser
        ref = FIRDatabase.database().reference()
        loadStudentInfo()
       // print(student_uid)
        imageDP.layer.cornerRadius = imageDP.frame.size.width/2
        imageDP.clipsToBounds = true
        
    }
    
    //-----Fetching and loading student info from Firebase --
    func loadStudentInfo(){
        
        let fetchUser = ref.child("Students").queryOrderedByChild("userKey").queryEqualToValue(student_uid)
        fetchUser.observeSingleEventOfType(.Value, withBlock: { (snapshot) in
            
            for rest in  snapshot.children.allObjects as! [FIRDataSnapshot]{
                
                let value = rest.value! as? NSDictionary
                
                self.name.text = value!["name"] as? String
                self.country.text = value!["country"] as? String
                self.city.text = value!["city"] as? String
                self.mailID.text = value!["emailID"] as? String
                self.phone.text = value!["phone"] as? String
                self.university.text = value!["university"] as? String
                
                if let value2 = value!["PersonnalPreferences"] as? NSDictionary{
                    self.aboutme.text = value2["aboutMe"] as? String
                    self.smoke.text = value2["smoke"] as? String
                    self.drink.text = value2["drink"] as? String
                    self.food.text = value2["food"] as? String
                    self.room.text = value2["room"] as? String
                }
                
                self.setPhoto()
                
                //break
            }
        })
        
    }
    
    func setPhoto(){
        
        let fetchUser = ref.child("Images").child(student_uid)
        fetchUser.observeSingleEventOfType(.Value, withBlock: { (snapshot) in
           
            let imageUrl = snapshot.value!["displayPic"] as! String
            print(imageUrl)
            
            let x = NSURL(string: imageUrl)
            let dataOfPic = NSData(contentsOfURL: x!)
            self.imageDP.image = UIImage(data: dataOfPic!)
           
        })

        
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }



}
