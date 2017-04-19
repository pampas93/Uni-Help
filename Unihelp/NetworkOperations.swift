//
//  NetworkOperations.swift
//  Unihelp
//
//  Created by Sushanth on 4/17/17.
//  Copyright © 2017 SuProject. All rights reserved.
//

import Foundation
import Firebase
import FirebaseAuth
import FirebaseDatabase
import FirebaseStorage

struct NetworkOperations{
    
    let databaseRef = FIRDatabase.database().reference()
    let storageRef = FIRStorage.storage().reference()
    //-----implement getting url by saving the image into the storage
    func returnUrl(imageView : UIImage) -> NSURL{
        
        return NSURL()
    }
    
    func saveInfo(stuObject : StudentProfile){
        //-----creates user dictionary info
       let studentDatabaseEntry = convertIntoDictionary(stuObject)
        let keyOf = FIRAuth.auth()?.currentUser?.uid
        databaseRef.child("Students").child(keyOf!).setValue(studentDatabaseEntry)
        //----create database reference
        //------save user information
    }
    private func convertIntoDictionary(stuObject : StudentProfile)->[String : AnyObject]{
        
        var temp : [String : AnyObject]?
        temp!["displayPic"] = stuObject.displayPicUrl
        temp!["type"] = stuObject.type
        temp!["userKey"] = stuObject.userKey
        temp!["name"] = stuObject.name
        temp!["emailID"] = stuObject.emailID
        temp!["country"] = stuObject.country
        temp!["city"] = stuObject.city
         temp!["university"] = stuObject.university
         temp!["DOB"] = stuObject.DOB
        temp!["personnaProfile"] = stuObject.personnaProfile
        temp!["requiredProfile"] = stuObject.requiredProfile
        temp!["requiredHouse"] = stuObject.requiredHouse
        
        return temp!
    }
     func alertingTheError(title : String, extMessage intMessage : String, extVc intVc : UIViewController){
        let alertController = UIAlertController(title: title, message:intMessage, preferredStyle: .Alert)
        alertController.addAction(UIAlertAction(title: "ok", style: .Default, handler: nil))
        intVc.presentViewController(alertController, animated: true, completion: nil)
    }
    
    func signInWithEmailID(emailID : String, extPass intPass : String,extVC vC : UIViewController) {
        
        FIRAuth.auth()?.signInWithEmail(emailID, password: intPass, completion: { (user, error) in
            if error != nil {
                
                self.alertingTheError("Error!!", extMessage: error?.localizedDescription ?? "Cound not find the error", extVc: vC)
                
            }else{
                //segue to the  4 options screen by setting the information of the user
                print(#function)
            }
        })
    }
    func signInWithFBCredentials(credential:FIRAuthCredential,extVC vC : UIViewController){
        FIRAuth.auth()?.signInWithCredential(credential, completion: { (user, error) in
            if error != nil{
                //-----alert controller
               self.alertingTheError("Error!!", extMessage: error?.localizedDescription ?? "Could not find Error", extVc: vC)
            }else{
                //----perform segue getting the user information needed for the model
            }
        })
    }
    func signInWithFBCredentialsFirst(credential:FIRAuthCredential,extVC vC : UIViewController){
        FIRAuth.auth()?.signInWithCredential(credential, completion: { (user, error) in
            if error != nil{
                //-----alert controller
                  self.alertingTheError("Error!!", extMessage: error?.localizedDescription ?? "Could not find Error", extVc: vC)
            }else{
                //----perform segue to collecting more info page by setting the user email id photo
            }
        })
    }
    
  private func signInWithEmailIDFirstTime(emailID : String, extPass intPass : String,extVC vC : UIViewController) {
        
        FIRAuth.auth()?.signInWithEmail(emailID, password: intPass, completion: { (user, error) in
            if error != nil {
               self.alertingTheError("Error!!", extMessage: error?.localizedDescription ?? "Could not find Error", extVc: vC)
                                
            }else{
                //Call create user with email
                //------perform Segue to profile information section acquiring section
                
            }
        })
    }
    
    
   func createUserWithEmailID(emailID : String, extPass intPass : String,extVC vC : UIViewController){
        FIRAuth.auth()?.createUserWithEmail(emailID, password: intPass, completion: { (user, error) in
            if error == nil {
                //-----creates user by signing in using emailID
                self.signInWithEmailIDFirstTime(emailID, extPass: intPass, extVC: vC)
            }else{
                
           self.alertingTheError("Error!!", extMessage: error?.localizedDescription ?? "Could not find Error", extVc: vC)
                
                
            }
        })
    }
}
