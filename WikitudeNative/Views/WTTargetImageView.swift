//
//  WTTargetImageView.swift
//  Native Examples
//
//  Created by Max Meraner on 06/04/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import UIKit

class WTTargetImageView : UIView
{
    var targetImageViewTopConstraint:   NSLayoutConstraint!
    var viewHeight:                     CGFloat!
    
    func setupView(with imageNames: [String], topLayoutGuide:UILayoutSupport)
    {
        if ( nil != self.superview )
        {
            self.viewHeight = 100.0
            
            let lightGrayColorWithAlpha = UIColor.lightGray.withAlphaComponent(0.5)
            self.backgroundColor = lightGrayColorWithAlpha
            self.translatesAutoresizingMaskIntoConstraints = false
            
            let views: Dictionary = ["self": self]
            self.superview!.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "|[self]|", options: NSLayoutConstraint.FormatOptions(rawValue: 0), metrics: nil, views: views))
            
            self.targetImageViewTopConstraint = NSLayoutConstraint.init(item: self,
                                                                        attribute: NSLayoutConstraint.Attribute.top,
                                                                        relatedBy: NSLayoutConstraint.Relation.equal,
                                                                        toItem: topLayoutGuide,
                                                                        attribute: NSLayoutConstraint.Attribute.bottom,
                                                                        multiplier: 1.0,
                                                                        constant: -self.viewHeight)
            self.superview!.addConstraint(self.targetImageViewTopConstraint)
            
            let targetImateViewHeightConstraint = NSLayoutConstraint.init(item: self,
                                                                          attribute: NSLayoutConstraint.Attribute.height,
                                                                          relatedBy: NSLayoutConstraint.Relation.equal,
                                                                          toItem: nil,
                                                                          attribute: NSLayoutConstraint.Attribute.notAnAttribute,
                                                                          multiplier: 1.0,
                                                                          constant: self.viewHeight)
            self.addConstraint(targetImateViewHeightConstraint)
            
            self.setupContainerViewWithImages(imageNames)
        }
        else
        {
            print("WTTargetImageView is not connected to a superview. Please call setupView(with:topLayoutGuide:) after adding the WTTargetImageView to a superview.")
        }
    }
    
    /*
     This function creates a container UIView and adds a UIImageView for each image in the received images array.
     It further sets up the autoLayout behavior of every element in the container UIView and also adds a label if it fits the view.
     The images are added from left to right.
     */
    private func setupContainerViewWithImages(_ imageNames:[String])
    {
        let imageWidth: CGFloat = 60.0
        let xOffset: CGFloat = 10.0
        
        let containerView: UIView = UIView()
        containerView.translatesAutoresizingMaskIntoConstraints = false
        self.addSubview(containerView)
        
        let label: UILabel = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = (imageNames.count == 1) ? "Target image:" : "Target images:"
        label.sizeToFit()
        
        var containerWidth: CGFloat = label.intrinsicContentSize.width + (imageWidth + xOffset) * CGFloat(imageNames.count)
        var lastAddedView: UIView = UIView()
        
        let omitLabel: Bool = self.superview!.bounds.size.width < containerWidth
        if ( omitLabel )
        {
            containerWidth -= label.intrinsicContentSize.width + xOffset
        }
        else
        {
            containerView.addSubview(label)
            
            let labelSuperView: UIView! = label.superview
            
            let views: Dictionary = ["label": label, "labelSuperView": labelSuperView!]
            labelSuperView.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "|[label]", options: NSLayoutConstraint.FormatOptions(rawValue: 0), metrics: nil, views: views))
            labelSuperView.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:[labelSuperView]-(<=1)-[label]", options: NSLayoutConstraint.FormatOptions.alignAllCenterY, metrics: nil, views: views))
            
            lastAddedView = label
        }
        
        for i in 0...imageNames.count-1
        {
            let imageView: UIImageView = UIImageView.init(image: UIImage.init(named: imageNames[i]))
            imageView.translatesAutoresizingMaskIntoConstraints = false
            imageView.contentMode = UIView.ContentMode.scaleAspectFit
            containerView.addSubview(imageView)
            
            if (i == 0 && omitLabel)
            {
                let imageViewLeftConstraint = NSLayoutConstraint.init(item: imageView,
                                                                      attribute: NSLayoutConstraint.Attribute.left,
                                                                      relatedBy: NSLayoutConstraint.Relation.equal,
                                                                      toItem: imageView.superview,
                                                                      attribute: NSLayoutConstraint.Attribute.left,
                                                                      multiplier: 1.0,
                                                                      constant: 0.0)
                imageView.superview!.addConstraint(imageViewLeftConstraint)
            }
            else
            {
                let imageViewTrailingConstraint = NSLayoutConstraint.init(item: imageView,
                                                                          attribute: NSLayoutConstraint.Attribute.leading,
                                                                          relatedBy: NSLayoutConstraint.Relation.equal,
                                                                          toItem: lastAddedView,
                                                                          attribute: NSLayoutConstraint.Attribute.trailing,
                                                                          multiplier: 1.0,
                                                                          constant: xOffset)
                imageView.superview!.addConstraint(imageViewTrailingConstraint)
            }
            
            let imageViewTopConstraint = NSLayoutConstraint.init(item: imageView.superview!,
                                                                 attribute: NSLayoutConstraint.Attribute.top,
                                                                 relatedBy: NSLayoutConstraint.Relation.equal,
                                                                 toItem: imageView,
                                                                 attribute: NSLayoutConstraint.Attribute.top,
                                                                 multiplier: 1.0,
                                                                 constant: -5.0)
            
            let imageViewBottomConstraint = NSLayoutConstraint.init(item: imageView.superview!,
                                                                    attribute: NSLayoutConstraint.Attribute.bottom,
                                                                    relatedBy: NSLayoutConstraint.Relation.equal,
                                                                    toItem: imageView,
                                                                    attribute: NSLayoutConstraint.Attribute.bottom,
                                                                    multiplier: 1.0,
                                                                    constant: 5.0)
            
            let imageViewWidthConstraint = NSLayoutConstraint.init(item: imageView,
                                                                   attribute: NSLayoutConstraint.Attribute.width,
                                                                   relatedBy: NSLayoutConstraint.Relation.greaterThanOrEqual,
                                                                   toItem: nil,
                                                                   attribute: NSLayoutConstraint.Attribute.notAnAttribute,
                                                                   multiplier: 1.0,
                                                                   constant: imageWidth)
            
            imageView.superview!.addConstraint(imageViewTopConstraint)
            imageView.superview!.addConstraint(imageViewBottomConstraint)
            imageView.addConstraint(imageViewWidthConstraint)
            
            lastAddedView = imageView
        }
        
        let superview: UIView = containerView.superview!
        let views = ["containerView": containerView, "superview": superview]
        
        containerView.superview!.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:|[containerView(==superview)]|", options: NSLayoutConstraint.FormatOptions(rawValue: 0), metrics: nil, views: views))
        
        let containerViewCenterXConstraint = NSLayoutConstraint.init(item: containerView,
                                                                     attribute: NSLayoutConstraint.Attribute.centerX,
                                                                     relatedBy: NSLayoutConstraint.Relation.equal,
                                                                     toItem: containerView.superview!,
                                                                     attribute: NSLayoutConstraint.Attribute.centerX,
                                                                     multiplier: 1.0,
                                                                     constant: 0.0)
        containerView.superview!.addConstraint(containerViewCenterXConstraint)
        
        let containerViewWidthConstraint = NSLayoutConstraint.init(item: containerView,
                                                                   attribute: NSLayoutConstraint.Attribute.width,
                                                                   relatedBy: NSLayoutConstraint.Relation.equal,
                                                                   toItem: nil,
                                                                   attribute: NSLayoutConstraint.Attribute.notAnAttribute,
                                                                   multiplier: 1.0,
                                                                   constant: containerWidth)
        containerView.addConstraint(containerViewWidthConstraint)
    }
    
    func show(animated: Bool)
    {
        DispatchQueue.main.async
        {
            if ( animated )
            {
                if ( -self.viewHeight == self.targetImageViewTopConstraint.constant )
                {
                    self.alpha = 1.0
                    self.superview!.layoutIfNeeded()
                    self.targetImageViewTopConstraint.constant = 0
                    UIView.animate(withDuration: 0.5, animations: {
                        self.superview!.layoutIfNeeded()
                    })
                }
            }
            else
            {
                if ( 0.0 == self.alpha )
                {
                    self.targetImageViewTopConstraint.constant = 0
                    self.alpha = 1.0
                }
            }
        }
    }
    
    func hide(animated: Bool)
    {
        DispatchQueue.main.async
        {
            if ( animated )
            {
                if ( 0 == self.targetImageViewTopConstraint.constant )
                {
                    self.superview!.layoutIfNeeded()
                    self.targetImageViewTopConstraint.constant = -self.viewHeight
                    UIView.animate(withDuration: 0.5, animations: { 
                        self.superview!.layoutIfNeeded()
                    }, completion: { (finished: Bool) in
                        self.alpha = 0.0
                    })
                }
            }
            else
            {
                if ( 1.0 == self.alpha )
                {
                    self.targetImageViewTopConstraint.constant = -self.viewHeight
                    self.alpha = 0.0
                }
            }
        }
    }
}
