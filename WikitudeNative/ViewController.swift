//
//  ViewController.swift
//  WikitudeNative
//
//  Created by Saroj Tiwari on 04/05/2022.
//

import UIKit
import AVKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Camera
        
        AVCaptureDevice.requestAccess(for: .video) { response in
            if response {
                // Video Access Given
            } else {
                // Video Access Not Given
            }
        }
        // Do any additional setup after loading the view.
    }
    @IBAction func startActionTapped(_ sender: Any) {
        let wikitude = WikitudeViewController()
        wikitude.modalPresentationStyle = .fullScreen
        self.present(wikitude, animated: true, completion: nil)
    }
    

}

