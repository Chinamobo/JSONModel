//
//  JSONModel.h
//
//  @version 0.8.4
//  @author Marin Todorov, http://www.touch-code-magazine.com
//

// Copyright (c) 2012 Marin Todorov, Underplot ltd.
// This code is distributed under the terms and conditions of the MIT license.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// The MIT License in plain English: http://www.touch-code-magazine.com/JSONModel/MITLicense

#import <Foundation/Foundation.h>

#import "JSONModelError.h"
#import "JSONValueTransformer.h"
#import "JSONKeyMapper.h"

/////////////////////////////////////////////////////////////////////////////////////////////
#if TARGET_IPHONE_SIMULATOR
#define JMLog( s, ... ) NSLog( @"[%@:%d] %@", [[NSString stringWithUTF8String:__FILE__] \
lastPathComponent], __LINE__, [NSString stringWithFormat:(s), ##__VA_ARGS__] )
#else
#define JMLog( s, ... )
#endif
/////////////////////////////////////////////////////////////////////////////////////////////
#if !__has_feature(objc_arc)
#error The JSONMOdel framework is ARC only, you can enable ARC on per file basis.
#endif
/////////////////////////////////////////////////////////////////////////////////////////////

#pragma mark - Property Protocols
/** 
 * Protocol for defining optional properties in a JSON Model class. Use like below to define 
 * model properties that are not required to have values in the JSON input:
 * 
 * @property (strong, nonatomic) NSString&lt;Optional&gt;* propertyName;
 *
 */
@protocol Optional
@end

/**
 * Protocol for defining index properties in a JSON Model class. Use like below to define
 * model properties that are considered the Model's identifier (id).
 *
 * @property (strong, nonatomic) NSString&lt;Index&gt;* propertyName;
 *
 */
@protocol Index
@end

/**
 * ConvertOnDemand enables lazy model initialization for NSArrays of models
 *
 * @property (strong, nonatomic) NSArray&lt;JSONModel, ConvertOnDemand&gt;* propertyName;
 */
@protocol ConvertOnDemand
@end

/////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - JSONModel protocol
/**
 * A protocol describing an abstract JSONModel class
 * JSONModel conforms to this protocol, so it can use itself abstractly
 */
@protocol AbstractJSONModelProtocol <NSObject>

@required
  /**
   * All JSONModel classes should implement initWithDictionary:
   *
   * For most classes the default initWithDictionary: inherited from JSONModel itself
   * should suffice, but developers have the option ot also overwrite it if needed.
   *
   * @param dict a dictionary holding JSON objects, to be imported in the model.
   * @param err an error or NULL
   */
  -(instancetype)initWithDictionary:(NSDictionary*)dict error:(NSError**)err;

  /**
   * All JSONModel classes should be able to export themselves as a dictioanry of
   * JSON compliant objects. 
   *
   * For most classes the inherited from JSONModel default toDictionary implementation
   * should suffice.
   *
   * @return NSDictionary dictionary of JSON compliant objects
   * @exception JSONModelTypeNotAllowedException thrown when one of your model's custom class properties 
   * does not have matching transformer method in an JSONValueTransformer.
   * @see JSONValueTransformer JSONObjectFromNSURL: for an example how to export custom class property to a JSON compliant object
   */
  -(NSDictionary*)toDictionary;
@end

/////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - JSONModel interface
/**
 * The JSONModel is an abstract model class, you should ot instantiate it directly,
 * as it does not have any properties, and therefore cannot serve as a data model.
 * Instead you should subclass it, and define the properties you want your data model
 * to have as properties of your own class.
 */
@interface JSONModel : NSObject <AbstractJSONModelProtocol>

/** @name Creating and initializing models */

  /**
   * Create a new model instance and initialize it with the JSON from a text parameter. The method assumes UTF8 encoded input text.
   * @param string JSON text data
   * @param err an initialization error or nil
   * @exception JSONModelTypeNotAllowedException thrown when unsported type is found in the incoming JSON, 
   * or a property type in your model is not supported by JSONValueTransformer and its categories
   * @see initWithString:usingEncoding:error: for use of custom text encodings
   */
  -(instancetype)initWithString:(NSString*)string error:(JSONModelError**)err;

  /**
   * Create a new model instance and initialize it with the JSON from a text parameter using the given encoding.
   * @param string JSON text data
   * @param encoding the text encoding to use when parsing the string (see NSStringEncoding)
   * @param err an initialization error or nil
   * @exception JSONModelTypeNotAllowedException thrown when unsported type is found in the incoming JSON, 
   * or a property type in your model is not supported by JSONValueTransformer and its categories
   */
  -(instancetype)initWithString:(NSString *)string usingEncoding:(NSStringEncoding)encoding error:(JSONModelError**)err;

  -(instancetype)initWithDictionary:(NSDictionary*)dict error:(NSError **)err;

/** @name Exporting model contents */

  -(NSDictionary*)toDictionary;

  /**
   * Export the whole object to a JSON data text string
   * @return JSON text describing the data model
   */
  -(NSString*)toJSONString;

/** @name Batch methods */

  /**
   * If you have a list of dictionaries in a JSON feed, you can use this method to create an NSArray
   * of model objects. Handy when importing JSON data lists.
   * This method will loop over the input list and initialize a data model for every dictionary in the list.
   *
   * @param array list of dictionaries to be imported as models
   * @return list of initialized data model objects
   * @exception JSONModelTypeNotAllowedException thrown when unsported type is found in the incoming JSON, 
   * or a property type in your model is not supported by JSONValueTransformer and its categories
   * @exception JSONModelInvalidDataException thrown when the input data does not include all required keys
   * @see arrayOfDictionariesFromModels:
   */
  +(NSMutableArray*)arrayOfModelsFromDictionaries:(NSArray*)array;

  /**
   * If you have an NSArray of data model objects, this method takes it in and outputs a list of the 
   * matching dictionaries. This method does the opposite of arrayOfObjectsFromDictionaries:
   * @param array list of JSONModel objects
   * @return a list of NSDictionary objects
   * @exception JSONModelTypeNotAllowedException thrown when unsported type is found in the incoming JSON, 
   * or a property type in your model is not supported by JSONValueTransformer and its categories
   * @see arrayOfModelsFromDictionaries:
   */
  +(NSMutableArray*)arrayOfDictionariesFromModels:(NSArray*)array;

/** @name Comparing models */

  /**
   * The name of the model's property, which is considered the model's unique identifier.
   * You can define Index property by using the Index protocol:
   * @property (strong, nonatomic) NSString&lt;Index&gt;* id;
   */
  @property (strong, nonatomic, readonly) NSString* indexPropertyName;

  /**
   * Overriden NSObject method to compare model objects. Compares the &lt;Index&gt; property of the two models,
   * if an index property is defined.
   * @param object a JSONModel instance to compare to for equality
   */
  -(BOOL)isEqual:(id)object;

  /**
   * Comparision method, which uses the defined &lt;Index&gt; property of the two models, to compare them.
   * If there isn't an index property throws an exception. If the Index property does not have a compare: method
   * also throws an exception. NSString and NSNumber have compare: methods, and in case the Index property is 
   * a another custom class, the programmer should create a custom compare: method then.
   * @param object a JSONModel instance to compare to
   */
  -(NSComparisonResult)compare:(id)object;

/** @name Validation */

  /**
   * Overwrite the validate method in your own models if you need to perform some custom validation over the model data.
   * This method gets called at the very end of the JSONModel initializer, thus the model is in the state that you would
   * get it back when initialzed. Check the values of any property that needs to be validated and if any invalid values
   * are encountered return NO and set the error parameter to an NSError object. If the model is valid return YES.
   *
   * NB: Only setting the error parameter is not enough to fail the validation, you also need to return a NO value.
   *
   * @param error a pointer to an NSError object, to pass back an error if needed
   * @return a BOOL result, showing whether the model data validates or not. You can use the convenience method
   * [JSONModelError errorModelIsInvalid] to set the NSError param if the data fails your custom validation
   */
-(BOOL)validate:(NSError**)error;

/** @name Key mapping */
  /**
   * Overwrite in your models if your property names don't match your JSON key names.
   * Lookup JSONKeyMapper docs for more details.
   */
+(JSONKeyMapper*)keyMapper;

@end
